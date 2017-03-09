import filecmp
from collections import defaultdict, namedtuple
from docutils import nodes
import re

DEV_PIN_TEST = None
DEV_DOCTREES = None
DEV_PLAINTEXT = None
DEV_DATA = None

def debug(context, *arg, **kwargs):
	"""Idiomatic debug printing."""
	# not perfect, but I like this idea and haven't seen a better way that doesn't involve throwing vastly more firepower at the problem.
	print(context, *arg, sep=u"\n----> ", **kwargs)


def interrogate(context, *arg, **kwargs):
	"""
	Debug after filtering out non-true values.

	This is to conditionally include/exclude individual messages in a bigger debug statement.
	"""
	return debug(context, *filter(None, arg), **kwargs)


class Validator(object):
	"""
	Basic validator functionality.
	"""
	app = name = doc = codes = lineno = infraction_type = None
	lint_summary = []
	doc_infractions = defaultdict(lambda: defaultdict(list))
	code_infractions = defaultdict(list)
	infraction = namedtuple('LinterInfraction', ["type", "code", "doc", "line", "message"])
	infraction_severity = defaultdict(int)

	@classmethod
	def lint(cls):
		raise NotImplementedError

	@classmethod
	def _register_infraction(cls, severity, code, lineno, **kw):
		"""Register linter infractions for later summarization."""
		sub_code = code.format(**kw)
		infraction = cls.infraction(type=severity, code=sub_code, doc=cls.name, line=lineno, message=cls.codes[code](**kw))
		cls.doc_infractions[cls.name][lineno].append(
			infraction
		)
		cls.code_infractions[sub_code].append(infraction)
		# TODO: for now we just count, but we may later append infraction here as well if we need to bisect reports this way
		cls.infraction_severity[severity] += 1

	@classmethod
	def _fail(cls, code, lineno, **kw):
		"""Alert about a linter error that will block."""
		cls._register_infraction("fail", code, lineno, **kw)

	@classmethod
	def _future(cls, code, lineno, **kw):
		"""Alert about a linter 'error' that won't block for now, but will at some future date."""
		cls._register_infraction("fail-future", code, lineno, **kw)

	@classmethod
	def _warn(cls, code, lineno, **kw):
		"""Alert about some linting issue that isn't strong enough to block build over."""
		cls._register_infraction("warn", code, lineno, **kw)

	@classmethod
	def _infraction(cls, severity, code, lineno, **kw):
		"""Generic alert without pre-set severity (for alerting mixed-severity infraction types)."""
		cls._register_infraction(severity, code, lineno, **kw)

	@classmethod
	def _purge_doc(cls, app, env, docname):
		# RESUME:
		# - move all infractions into env or domaindata,
		# - stop collecting by-code infractions/counts and instead compile these on final report
		# - guard final report with an env or tag
		# - squelch output if not tag?
		cls.doc_infractions.pop(docname, None)

	long_sphinx_fmt = {
		re.compile(r'(?P<element>.+?) ends without a blank line; unexpected unindent.'): '\g<element> ends without blank line',
		re.compile(r'Error in "(?P<directive>.+?)" directive:'): 'Error in "\g<directive>" directive',
		re.compile(r'Duplicate explicit target name: "(?P<target>.+?)".'): '"\g<target>" already defined',
		re.compile(r'duplicate (?P<domain>.+?) object description of (?P<target>.+?), other instance in .*?/source/(?P<doc>.+?)\.rst'): '"\g<target>" already defined in \g<doc>',
		re.compile(r"toctree contains reference to nonexisting document '(?P<target>.+?)'"): 'toctree references missing doc "\g<target>"',
		re.compile(r"toctree contains reference to document (?P<target>.+?) that doesn't have a title: no link will be generated"): "toctree can't generate link to untitled doc \g<target>",
		re.compile(r"more than one target found for '(?P<role>.+?)' cross-reference (?P<target>.+?): could be (?P<roles>.+?)"): "ambiguous cross-ref '\g<target>' could be \g<roles>",
		re.compile(r'broken link: (?P<link>.+?) \('): 'broken link to \g<link>',
	}
	long_sphinx_msg = {
		'Substitution definition contains illegal element:': 'Substitution definition contains illegal element',
		'glossary terms must not be separated by empty lines': 'no blank lines between glossary terms',
		'Inline interpreted text or phrase reference start-string without end-string.': 'mismatched interpreted text quotes (`)',
		'Inline emphasis start-string without end-string.': 'mismatched emphasis text quotes (*)',
		'Inline strong start-string without end-string.': 'mismatched strong text quotes (**)',
		'Inline literal start-string without end-string.': 'mismatched literal text quotes (``)',
		'exception while evaluating only directive expression:': 'exception in "only" directive',

	}
	clean = re.compile('\s\((DEBUG|INFO||WARNING|ERROR|SEVERE)/\d\)\s')

	@classmethod
	def _clean_sphinx_msg(cls, msg):
		msg = msg.splitlines()[0]
		msg = cls.clean.sub("", msg)
		if msg in cls.long_sphinx_msg:
			return cls.long_sphinx_msg[msg]

		for rule, template in cls.long_sphinx_fmt.items():
			match = rule.match(msg)
			if match:
				return match.expand(template)

		return msg


	@classmethod
	def _ingest_sphinx_record(cls, record):

		severity = cls._translate_loglevel(record.levelno)
		if severity is None:
			print("UNDERWHELMING RECORD", record.__dict__)
			return

		code = []
		# either need to ditch this information or filter the sphinx codes down; they're awkwardly long in output
		# code = ["sphinx"]
		if record.name.endswith("docutils"):
			code = ["docutils"]

		loc = doc = line = msg = None

		#print("UNDERWHELMING RECORD", record.__dict__)
		msg = (record.msg % record.args) if len(record.args) else record.msg

		if record.location:
			loc = record.location.split(":")
			if len(loc) > 1:
				doc, line = loc[:2]
				line = int(line)
			else:
				doc = loc[0]
				line = -1
		else:
			loc = record.msg.split(":")
			doc = loc[0]
			if len(loc) > 1 and loc[1].isdigit():
				line = int(loc[1])
				msg = ":".join(loc[2:])
			else:
				line = -1
				msg = ":".join(loc[1:])

		# if len(loc) > 2:
		# 	doc, line = loc[:2]
		# 	msg = ":".join(loc[2:])
		# elif len(loc) > 1:
		# 	doc, line = loc
		#
		doc = doc[len(cls.app.srcdir)+1:-4] # strip out the source dir and extension

		if 'type' in record.__dict__ and record.type:
			code.append(record.type)
		if 'subtype' in record.__dict__ and record.subtype:
			code.append(record.subtype)

		sub_code = "-".join(code or ["sphinx"])

		infraction = cls.infraction(type=severity, code=sub_code, doc=doc, line=line, message=cls._clean_sphinx_msg(msg))
		cls.doc_infractions[doc][line].append(infraction)
		cls.code_infractions[sub_code].append(infraction)

	@staticmethod
	def _translate_loglevel(level):
		if level < logging.WARNING:
			return None
		elif level < logging.ERROR:
			return "future"
		elif level >= logging.ERROR:
			return "fail-future"
		else:
			return "warn"

	@classmethod
	def init_state(cls):
		"""
		Overload: initialize all state linter needs before run.

		At the absolute minimum, 'app' and 'name' must be set.
		"""
		raise NotImplementedError

	@classmethod
	def clear_state(cls):
		"""Overload: clear all linter state."""
		raise NotImplementedError

	@classmethod
	def _node_docname(cls, node):
		"""Walk up the tree looking for a good docname."""
		temp = node
		docname = None

		while docname is None and temp:
			# there are 3 places we might find it; docname, refdoc, or source
			for location in ("refdoc", "docname", "source"):
				docname = temp.get(location, None)
				if docname:
					break

			temp = temp.parent

		# scrub any common substring with srcdir
		# technically this will do the "wrong" thing if we get a docname that starts with srcdir but lacks a file extension, since we indiscriminately lop off the last 4 characters.
		# pylint: disable=no-member
		docname = docname[len(cls.env.srcdir) + 1:-4] if docname.startswith(cls.env.srcdir) else docname

		assert docname is not None
		return docname

	@staticmethod
	def _node_line(node):
		temp = node
		lineno = node.line
		while lineno is None and temp.parent:
			temp = temp.parent
			lineno = temp.line

		return lineno if lineno is not None else -1

	@classmethod
	def summary(cls, app, exc):  # pylint: disable=unused-argument
		"""Summarize lint errors stored on the Validator class by various subclassed validators."""
		# pylint: disable=protected-access
		# if there were warnings, add our linting message
		if app._warncount or cls.infraction_severity["fail"]:
			# TODO: a bit of a lie, oui?
			app.info("Though the documentation has been built, there were errors.")
			app.statuscode = 1

		if len(cls.code_infractions):
			print("The LDMud documentation linter encountered issues with the docs; a list of infractions will be printed below, followed by a tabular summary of all issues.")
			sorted_docs = sorted(cls.doc_infractions)
			sorted_codes = sorted(cls.code_infractions)
			max_code_len = max(map(len, sorted_codes))
			doc_infraction_template = "{:>5} | {:>%d}: {:<%d}" % (max_code_len, 70 - max_code_len)

			for doc in sorted_docs:
				print(doc)
				for line in sorted(cls.doc_infractions[doc].keys()):
					infractions = cls.doc_infractions[doc][line]
					for infraction in infractions:
						print(doc_infraction_template.format(line if line > -1 else "?", infraction.code, infraction.message))
				print("")

			print("")
			print("{:-^65}".format("[Linter stats]"))

			# infractions-by-document table
			print("  {:<40} | {:>6}".format("document", "count"))
			print("-" * 55)
			for doc in sorted_docs:
				print("  {:<40} | {:>6}".format(doc, sum(map(len, cls.doc_infractions[doc].values()))))
			print("")

			# infractions-by-code table
			print("  {:<40} | {:>6}".format("code", "count"))
			print("-" * 55)
			for code in sorted_codes:
				print("  {:<40} | {:>6}".format(code, len(Validator.code_infractions[code])))
			print("")

			# severity table
			print("  {:<40} | {:>6}".format("severity", "count"))
			print("-" * 55)
			for severity, count in cls.infraction_severity.items():
				print("  {:<40} | {:>6}".format(severity, count))
			print("")

			# TODO: add a message about the docutils/sphinx errors that we'll fail for but which might be buried above all of our output?
			#
			print("-" * 55)
			for line in cls.lint_summary:
				print(line)

			if app.statuscode:
				# if we have a statuscode, the exit code we throw will stop the makefile from printing the output directory; simplest fix is printing it here
				print("Build finished. The '{:}' files are in {:}/".format(app.builder.name, app.outdir))


class Usage(Validator):
	@classmethod
	def init_state(cls, node, lint_codes): # pylint: disable=arguments-differ
		cls.codes = lint_codes
		cls.env = node.document.settings.env
		cls.name = node.document.settings.env.docname
		cls.lineno = node.line

	@classmethod
	def clear_state(cls):
		cls.codes = cls.env = cls.name = cls.lineno = None


class Source(Validator):
	"""
	Enforces generic codestyle rules.

	Rules of this kind should be testable with simple heuristics and 0 semantic knowledge.

	1: Nothing but directives and comments at the document level; this means a line should be blank, should begin with two periods and a space, or should have some quantity of blank spaces (probably coming in pairs)
	2: Only valid directives are used at the top level of a document:
		efun, master, hook...

	TODO:
		- blank lines aren't *always* ok; should we try to specify when they are and aren't?

	"""
	INDENT_STEP = 2
	stack = None
	codes = {
		# pylint: disable=unnecessary-lambda
		# disabled the line-too-long rule, but saving for posterity
		# "line-too-long": lambda n: "len: {:} (max: {:})".format(n, Source.MAX_SOURCE_LINE_LEN),
		"indent-under": lambda n, expected: "found {:>2} spaces, expected {:>2}".format(n, expected),
		"indent-over": lambda n, expected: "found {:>2} spaces, expected {:>2}".format(n, expected)
	}

	@classmethod
	def init_state(cls, app, docname, source):  # pylint: disable=arguments-differ
		cls.app = app
		cls.name = docname
		cls.doc = source
		cls.lineno = 0
		cls.stack = [cls.document]

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = cls.name = cls.doc = cls.lineno = cls.stack = None

	@classmethod
	def lint(cls, app, docname, source):  # pylint: disable=arguments-differ
		cls.init_state(app, docname, source)
		for block in cls.doc:
			print("BETA BLOCKERS", block)
			for line in block.splitlines():
				cls.lineno += 1

				while cls.stack[-1](line) is False:
					cls.stack.pop()
		cls.clear_state()

	@classmethod
	def handle_directive(cls, line, indent):
		"""Returns True if the line has been handled"""
		directive, comment = cls.find_directive(line, indent)
		if directive:
			# It's tempting to validate directives here, but it's a fool's errand; this validator should stick to structure/style and leave directives to the tree linter
			cls.stack.append(cls.directive(len(cls.stack)))
			return True
		elif comment:
			# this should be a comment line, but I haven't decided if we allow comments or not...
			cls.stack.append(cls.directive(len(cls.stack)))  # allow for now I guess...
			return True  # OK for now

	@classmethod
	def handle_field(cls, line, indent):
		"""Returns True if the line has been handled"""
		field = cls.find_field(line, indent)
		if field:
			# It's tempting to validate fields here, but it's a fool's errand; stick to structure/style
			cls.stack.append(cls.field(len(cls.stack)))
			return True

	@classmethod
	def handle_markup(cls, line, indent):
		"""Returns True if the line has been handled"""

		if cls.find_markup(line, indent):
			cls.stack.append(cls.markup(len(cls.stack)))
			return True

	@staticmethod
	def find_markup(line, indent):
		if line.startswith((" " * (indent + 2))):
			if line[indent + 2] == " ":
				return False
			else:
				return True

	@staticmethod
	def find_field(line, indent):
		if line.startswith((" " * indent) + ":"):
			try:
				return line[indent + 1:line.index(":", indent + 1)]
			except ValueError:
				return False
		return False

	@staticmethod
	def find_directive(line, indent):
		if line.startswith((" " * indent) + ".."):
			try:
				return line[indent + 3:line.index(":")], False
			except ValueError:
				return False, True
		return False, False

	@classmethod
	def document(cls, line):
		"""Lint bare document lines."""
		if not len(line):
			return True

		# if cls.handle_directive(line, 0):
		# 	return True

		# if cls.handle_field(line, 0):
		# 	return True

	@classmethod
	def _generate_indent_linter(cls, pad):
		def indent_linter(line):
			if not len(line):  # TODO: yuck; would like to catch this earlier
				return True  # OK

			indented = len(line) - len(line.lstrip())

			if indented == pad:
				# indent is exactly right
				if cls.handle_directive(line, pad):
					return True  # OK
				elif cls.handle_field(line, pad):
					return True
			elif indented > pad:
				if cls.handle_markup(line, pad):
					return True

				cls._fail("indent-over", cls.lineno, n=indented, expected=pad)  # indent-over
				return True
			elif not indented % cls.INDENT_STEP:
				# indent is divisible by our step
				return False
			else:
				cls._fail(
					"indent-under",
					cls.lineno,
					n=indented,
					expected=pad
				)
				return True
		return indent_linter

	@classmethod
	def indent(cls, depth):
		pad = depth * cls.INDENT_STEP  # cols to indent

		return cls._generate_indent_linter(pad)

	field = indent
	directive = indent
	markup = indent

# TODO: this validator doesn't catch refs with a bad role (i.e., a typo, or a role we've renamed/removed); we'll need to catch those as docutils/sphinx surface errors. Message format:
# home/lddoc/source/index.rst:11: (ERROR/3) Unknown interpreted text role "directory". [filtered system message]
class References(Validator):
	codes = {
		# pylint: disable=unnecessary-lambda
		"ref-unresolved": lambda target: "unresolved reference to {:}".format(target),
	}

	# cache the most recent doc so we don't have to go look up the path every ref
	lastname = lastref = None

	@classmethod
	def init_state(cls, app, env, node):  # pylint: disable=arguments-differ
		cls.app = app
		cls.env = env
		refdoc = cls._node_docname(node)

		if refdoc != cls.lastref:
			cls.lastname = cls.name = refdoc
			cls.lastref = refdoc  # TODO: probably superfluous
		else:
			cls.name = cls.lastname

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = cls.name = cls.env = None

	@classmethod
	def lint(cls, app, env, node, contnode):  # pylint: disable=arguments-differ,unused-argument
		cls.init_state(app, env, node)
		cls._fail("ref-unresolved", cls._node_line(node), target="%s:%s" % (node.get("reftype", "dunno"), node.get("reftarget", "dunno2")))
		cls.clear_state()


class Tree(Validator):
	"""
	Enforces specific structural and semantic rules.
	"""
	app = name = doc = codes = None

	@classmethod
	def init_state(cls, app, doctree, docname):  # pylint: disable=arguments-differ
		cls.app = app
		cls.name = docname
		cls.doc = doctree
		#print("TREE_IDS", doctree.ids if "ids" in doctree else None)
		DEV_DOCTREES and debug("dev_doctrees:", "full document tree", doctree)

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = cls.name = cls.doc = None


# TODO:
# - if it isn't easier to do with a setting on the todo extension, this should flag todos as at least a warning?
class Nodes(Tree):
	codes = {
		# TODO: don't expose abstractions ("child") to end users?
		"invalid-{child:}": lambda child, parent, choices: "{:} isn't a valid child of a {:} node".format(child, parent),  # formerly included: , ", ".join(choices)
		"requires-{child:}": lambda child, parent, template: template.format(parent, child),
	}
	rule = namedtuple('LinterNodeRuleMeta', ["severity", "template"])
	BASIC_BODY_NODES = [
		"section",
		"CrouchingTitle",  # TODO: the presence of this in the valid child list isn't super user-friendly
		"index"
	]
	PRIMARY_DOC_TYPES = [
		"command",
		"function",
		"hook",
		"applied",
		"lang", # this should go away?
		"syntax",
		"keyword",
		"type",
		"operator",
		"topic",
		"guide",
	]
	VALID_TOP_LEVEL_NODES = [
		"index",
		"section",
		"comment",
		"only",
	] + PRIMARY_DOC_TYPES
	REQUIRED_PRIMARY_CHILDREN = {  # TODO: note that these messages could be combined into a single one: "{:} documents should always include a {:} section"
		# "history": rule("fail-future", "{:} documents should have a history section"),
		# "seealso": rule("fail-future", "{:} documents should have a seealso section"),
	}
	valid = {
		"document": VALID_TOP_LEVEL_NODES,
		"function": BASIC_BODY_NODES,
		"hook": BASIC_BODY_NODES,
		"meta": [
			"paragraph",
			"todo_node"
		]
	}
	required = {
		"function": REQUIRED_PRIMARY_CHILDREN,
		"hook": REQUIRED_PRIMARY_CHILDREN,
		"topic": REQUIRED_PRIMARY_CHILDREN,
		"usage": {
			"paragraph": rule("fail-future", "usage sections should always include some explanation")
		},
	}

	@classmethod
	def valid_child(cls, node):
		# make sure we care about this node type.
		if node.parent and node.parent.tagname in cls.valid:
			if node.tagname in cls.valid[node.parent.tagname]:
				return True

			else:
				cls._infraction("fail", "invalid-{child:}", cls._node_line(node), child=node.tagname, parent=node.parent.tagname, choices=cls.valid[node.parent.tagname])
		else:
			if node.tagname in cls.valid:
				return True
			# don't review nodes we don't care about.
			return False

	@classmethod
	def lint(cls, app, doctree, docname):  # pylint: disable=arguments-differ
		cls.init_state(app, doctree, docname)
		cls.traverse(cls.doc)

	@classmethod
	def traverse(cls, top):
		for node in top.traverse(cls.valid_child):
			tag = node.tagname
			# if tag in cls.required:
			# 	kids = map(lambda x: x.tagname, node.children)
			# 	for req in cls.required[tag]:
			# 		if req not in kids:
			# 			cls._fail("required-child", cls.doc.line, child=req, parent=node.tagname)
			if hasattr(cls, tag):  # if I have a function <tag>, go ahead and pass this node to it for more explicit validation.
				getattr(cls, tag)(node)

			elif tag in cls.required:
				cls._deep_require_children(node)

	@classmethod
	def _deep_require_children(cls, target):
		targetname = target.tagname
		required = list(cls.required[targetname])
		for node in target.traverse():
			tag = node.tagname
			if tag in required:
				required.remove(tag)

			if not len(required):
				# success
				break

		for req in required:
			cls._infraction(cls.required[targetname][req].severity, "requires-{child:}", cls._node_line(target), child=req, parent=targetname, template=cls.required[targetname][req].template)

	@classmethod
	def history(cls, target):  # this isn't a node, it's an attrib
		return cls._deep_require_children(target)

	hook = _deep_require_children


# TODO:
# - the name of a defined arg
# - Any admonition name (note, warning...)
# - Smell words? "You", "obvious(ly)", "resp."
# - spot version numbers in running text (should be history notes?)
# - catch "nth argument" structures in favor of naming the arg?
# - sniff out numeric return values (should they be defined values?)
# - sniff out things that look like command flags? or are there just not enough to bother?
# - sniff out #'closure forms in running text?
# - sniff out untagged operators, pragmas in text?
# - sniff out non-standard forms of standardish values like true, false, null, etc.
# - identify any tense forms we want to discourage (i.e., prefer returns over returned, etc.)
# - line numbers are off if there's an include
# - sniff out literal constructors in running text?
# - sniff out block comments in code blocks
class Text(Tree):
	codes = {
		"text-{subcode:}": lambda subcode, match, template: template.format(match, subcode),
		"text-newline": lambda: "errant newline within element"
	}
	rule = namedtuple('LinterTextRuleMeta', ["regexp", "severity", "template"])
	TEXT_RULES = {
		'lpc-closure': rule(
			re.compile(r'#\'\S*'),
			'fail-future',
			'is "{:}" an lpc closure?'
		),
		'lpc-literal': rule(
			re.compile(r'\([[{<].*?[\]}>]\)'),
			'fail-future',
			'is "{:}" an lpc literal?'
		),
		'lpc-pragma': rule(
			re.compile(r'#pragma \w+(, \w+)*'),
			'fail-future',
			'is "{:}" an lpc pragma?'
		),
		'ref-macro': rule(
			re.compile(r'\b[A-Z_]{3,}\b'),
			'fail-future',
			'does "{:}" refer to a macro?'
		),
		'ref-arg': rule(
			re.compile(r'<\w+>'),
			'fail-future',
			'does "{:}" refer to a function argument?'
		),
		'ref-func': rule(
			re.compile(r'[a-zA-Z_0-9]{1,}(?!\([s!]\))(?!<\(s\))\(.*?\)'),
			'fail-future',
			'does "{:}" refer to a function/method?'
		),
		'space': rule(
			re.compile(r'\S+[,.!?;]\s{2,}'),
			'fail-future',
			'extra space at "{:}"'
		),
		'weasel-word': rule(
			re.compile(r'\b(resp\b\.|obvious\w+\b)'),
			'fail-future',
			'discouraged word "{:}"'
		)
	}

	@classmethod
	def lint(cls, app, doctree):  # pylint: disable=arguments-differ
		cls.init_state(app, doctree, app.env.docname)
		cls.validate_paragraphs(cls.doc)

	@classmethod
	def validate_text(cls, txt):
		for code, rule in cls.TEXT_RULES.items():
			for hit in rule.regexp.finditer(txt):
				cls._infraction(rule.severity, "text-{subcode:}", cls._node_line(txt), subcode=code, match=hit.group(), template=rule.template)

	@classmethod
	def validate_paragraph(cls, par):
		rawlines = par.rawsource.splitlines()
		if len(rawlines) > 1:
			startline = cls._node_line(par)
			for line in rawlines[:-1]:
				# if a line is blank
				if line == "":
					pass
				cls._future("text-newline", startline)
				startline += 1

	@classmethod
	def validate_paragraphs(cls, top):
		for par in top.traverse(nodes.paragraph):
			cls.validate_paragraph(par)
			for txt in par.traverse(nodes.Text):
				if isinstance(txt.parent, nodes.paragraph):
					cls.validate_text(txt)


class PinnedDocs(Validator):
	"""Not actually sharing much code with other validators."""

	# output files "pinned" as reference/test files whose output should not unintentionally slip while we work; as such, we raise hell if they change.
	# TODO: update these post-reorganization
	test_files = [
		# (reference_file_path, built_file_path)
		("master", "master/overview"),  # directory
		("predefined", "topics/predefined"),  # topic, macro
		#("ed", "LPC/ed"),  # command
		("init", "applied/init"),  # applied
		("input_to", "efun/input_to"),  # efun
		("privilege_violation", "master/privilege_violation"),  # master
		("default_method", "hook/default_method"),  # hook
		("codestyle", "internals/codestyle"),  # meta
		("parsing-inline-closures", "internals/parsing-inline-closures"),  # meta
		("negotiation", "topics/negotiation"),  # admonition (note, misleading)
		("modifiers", "syntax/modifiers"),  # modifier
		("int", "syntax/int"),  # type
		("foreach", "syntax/foreach"),  # lang, keyword
		("arrow", "syntax/arrow"),  # lang, operator
		("pragma", "syntax/pragma"),  # lang, pragma
		("functionlist", "efun/functionlist"),  # :include:
	]

	doxycode = ("efun", "master", "applied")

	pin_differs = 0

	@classmethod
	def notify_pinned_difference(cls, source, pinned, generated):
		if cls.pin_differs == 0:
			cls.lint_summary.append("\nOne or more pinned files differ from the generated output. You should manually compare them in case the output has unintentionally changed or regressed. Use the below commands to compare and (if appropriate) update the pinned file:\n")
		cls.pin_differs += 1

		cls.lint_summary.append("\n".join(
				(
					"	git diff --no-index --color-words=. {pinned:} {generated:}",
					"		cp {generated:} {pinned:}"
				)
			).format(pinned=pinned, generated=generated))
		# cls.app.env.warn(source,
		# 	"\n".join(
		# 		(
		# 			"Pinned file '{pinned:}' differs from generated '{generated:}'.",
		# 			"	You should manually compare the files in case output has unintentionally changed:",
		# 			"		git diff --no-index --color-words=. {pinned:} {generated:}",
		# 			"	If the output difference is expected, update the pinned file to current output with:",
		# 			"		cp {generated:} {pinned:}"
		# 		)
		# 	).format(pinned=pinned, generated=generated), "*")

	# TODO: below methods look ripe for a refactor
	@classmethod
	def diff_html(cls, source, pinned, generated):
		pinned = "pinned/%s.html" % pinned
		generated = "build/html/%s.html" % generated
		try:
			if filecmp.cmp(pinned, generated, shallow=False) is False:
				cls.notify_pinned_difference(source, pinned, generated)
		except FileNotFoundError:
			# can't diff as one of these files doesn't exist
			pass

	@classmethod
	def diff_plain(cls, source, pinned, generated):
		pinned = "pinned/%s" % pinned
		generated = "build/plain/%s" % generated
		try:
			if filecmp.cmp(pinned, generated, shallow=False) is False:
				cls.notify_pinned_difference(source, pinned, generated)
		except FileNotFoundError:
			# can't diff as one of these files doesn't exist
			pass

	@classmethod
	def diff_doxy(cls, source, pinned, generated):
		ext = "c" if generated.split("/")[0] in cls.doxycode else "md"
		pinned = "pinned/{:}.{:}".format(pinned, ext)
		generated = "build/doxygen/{:}.{:}".format(generated, ext)
		try:
			if filecmp.cmp(pinned, generated, shallow=False) is False:
				cls.notify_pinned_difference(source, pinned, generated)
		except FileNotFoundError:
			# can't diff as one of these files doesn't exist
			pass

	@classmethod
	def init_state(cls, app):  # pylint: disable=arguments-differ
		cls.app = app

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = None

	@classmethod
	def lint(cls, app, exception):  # pylint: disable=arguments-differ
		"""Uses build-finished event, which is called at end of Sphinx run with exception if one occurred."""
		if exception or not DEV_PIN_TEST:
			return

		cls.init_state(app)

		for pinned, generated in cls.test_files:
			source = generated
			cls.diff_html(source, pinned, generated)
			cls.diff_plain(source, pinned, generated)
			cls.diff_doxy(source, pinned, generated)

		DEV_DATA > 0 and debug("Temporary debug report on which object types are in use",
			{k: len(v or []) for k, v in app.env.domains['lpc'].data.items()},
			app.env.domains['lpc'].data if (DEV_DATA > 1) else None)

		debug("Temporary debug report on which object types are in use", {k: len(v or []) for k, v in app.env.domains['lpc'].data.items()})

		cls.clear_state()


class Todo(Validator):
	"""Not actually sharing much code with other validators."""

	codes = {
		"todo": lambda: "Pending todo",
	}

	@classmethod
	def init_state(cls, app):  # pylint: disable=arguments-differ
		cls.app = app
		cls.env = app.env

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = None
		cls.env = None

	@classmethod
	def lint(cls, app, todo):  # pylint: disable=arguments-differ
		"""TODO: Uses build-finished event, which is called at end of Sphinx run with exception if one occurred."""

		cls.init_state(app)
		cls.name = cls._node_docname(todo)
		cls._warn("todo", cls._node_line(todo))
		cls.clear_state()


class Topics(Validator):
	"""Not actually sharing much code with other validators."""

	codes = {
		"topic-trivial": lambda topic, refcount: "Topic '{topic:}' referenced only {refcount:}x.".format(topic=topic, refcount=refcount),
		"topic-undocumented": lambda topic, refcount: "'{topic:}' referenced {refcount:}x.".format(topic=topic, refcount=refcount),
		"topic-unreferenced": lambda topic: "'{topic:}' not referenced.".format(topic=topic),
	}
	name = "topic/*"

	@classmethod
	def init_state(cls, app):  # pylint: disable=arguments-differ
		cls.app = app

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = None

	@classmethod
	def lint(cls, app, exception):  # pylint: disable=arguments-differ
		"""Uses build-finished event, which is called at end of Sphinx run with exception if one occurred."""

		cls.init_state(app)

		topic_refs = [(topic, refs) for topic, refs in app.env.domains['lpc'].data['topics'].items() if len(refs) > 0]
		# all topics referenced more than N times must have a corresponding topic document.
		for topic, refs in topic_refs:
			if topic not in app.env.domains['lpc'].data['topic']:
				cls._fail(
					"topic-undocumented",
					-1,
					topic=topic,
					refcount=len(refs)
				)
			else:
				if len(refs) < 2:# TODO: 2 should be some sort of config/var
					cls._warn(
						"topic-trivial",
						-1,
						topic=topic,
						refcount=len(refs)
					)

		for topic in set(app.env.domains['lpc'].data['topic']).difference(set(app.env.domains['lpc'].data['topics'])):
			cls._fail(
				"topic-unreferenced",
				-1,
				topic=topic
			)
		cls.clear_state()


def set_dev_flags(app):
	"""
	Set globals based on develop_options config.

	Intentionally factored these options out into individual binary globals for the small time savings; some of these debug lines will have many thousands of chances to run.

	Note that while these are set here, it's only because we have to wait for Sphinx to set up its environment before we have config values; otherwise they should be treated as constants.
	"""
	# pylint: disable=global-statement
	global DEV_PIN_TEST, DEV_DOCTREES, DEV_PLAINTEXT, DEV_DATA
	# a dict is like a fistful of options
	dev = app.config.lddoc_develop_options
	DEV_PIN_TEST = dev["pinned"] or sum(dev.values()) > 0
	DEV_DOCTREES = dev["doctrees"]
	DEV_PLAINTEXT = dev["plaintext"]
	DEV_DATA = dev["data"]
	if DEV_PLAINTEXT > 5:
		LPCTextTranslator.__getattribute__ = LPCTextTranslator.report_calls


import sphinx.util.logging
import logging

class LPCLogHandler(logging.StreamHandler):
	def emit(self, record):
		Validator._ingest_sphinx_record(record)

lpchandler = logger = None
run_once = []

def end_first_builder(app, builder):
	global logger, lpchandler, run_once
	if len(run_once):
		logger.removeHandler(lpchandler)
	while len(run_once):
		app.disconnect(run_once.pop())


def lights_out(app, exception):
	Topics.lint(app, exception)
	PinnedDocs.lint(app, exception)
	Validator.summary(app, exception)


def heat_lamps(app):
	"""Builder is alive; get conf values & setup."""
	global logger, lpchandler, run_once
	set_dev_flags(app)
	Validator.app = app
	logger = logging.getLogger("sphinx")
	lpchandler = LPCLogHandler(app)
	lpchandler.addFilter(sphinx.util.logging.WarningSuppressor(app))
	lpchandler.addFilter(sphinx.util.logging.WarningLogRecordTranslator(app))
	lpchandler.setLevel(logging.WARNING)
	lpchandler.setFormatter(sphinx.util.logging.ColorizeFormatter())
	logger.addHandler(lpchandler)
	temp = logging.getLogger("sphinx.builders.linkcheck")
	temp.addHandler(lpchandler)
	run_once.append(app.connect('doctree-resolved', Nodes.lint))
	run_once.append(app.connect('doctree-read', Text.lint))
	run_once.append(app.connect('missing-reference', References.lint))
	run_once.append(app.connect('todo-defined', Todo.lint))
	app.connect('multi-builder-end-builder', end_first_builder)
