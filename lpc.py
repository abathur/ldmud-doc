# pylint: disable=missing-docstring, expression-not-assigned, too-many-ancestors

import re
from sphinx.locale import l_, _, admonitionlabels
from sphinx.domains import ObjType, Index
from sphinx.domains import c
import sphinx.domains.std
from sphinx.builders.text import TextBuilder
from docutils import nodes
from docutils.utils import column_width
from sphinx import addnodes
from sphinx.util.docfields import TypedField, DocFieldTransformer, _is_single_paragraph
from sphinx.util.nodes import make_refnode, set_source_info
from docutils.parsers.rst import directives
from sphinx.writers.text import TextTranslator, TextWrapper
from sphinx.writers.html import SmartyPantsHTMLTranslator
import operator
import itertools
import sys
import filecmp
import string
import copy
from collections import defaultdict, namedtuple, OrderedDict

# true constants
MAXWIDTH = 78  # wrap docs at

# global vars for gatekeeping development output; these are named like constants but we can't actually set values until Sphinx parses the config; see set_dev_flags()
DEV_PIN_TEST = None
DEV_DOCTREES = None
DEV_DOXYGEN = None
DEV_PLAINTEXT = None
DEV_REF = None


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


class CrouchingTitle(nodes.title, nodes.Invisible):
	"""
	Non-rendering title node.

	Fulfills docutils/sphinx expectations for where title nodes are in a document, but allows us to have things like SYNOPSIS or CONCEPT appear to be the title. Mostly necessary so that our TOC/link entries show the right title.
	"""

	def visit_title(self, node):  # pylint: disable=unused-argument, no-self-use
		raise nodes.SkipNode()


# TODO: something in here works fine for the history/typedfield kind, but falls flat on the include/groupedfield kind. The basics work now, but I either need to move the node, or figure out how to parse it out in a separate step when I parse out the synopsis.
# TODO: support repeating an argument to document different types (i.e., the format of arg X when both array or mapping are valid)
class LPCDocFieldTransformer(DocFieldTransformer):
	def transform(self, node):  # TODO: decompose, will fix many lint warnings
		"""Transform a single field list *node*."""
		typemap = self.typemap

		entries = []
		groupindices = {}
		types = {}

		# step 1: traverse all fields and collect field types and content
		for field in node:
			fieldname, fieldbody = field
			try:
				# split into field type and argument
				fieldtype, fieldarg = fieldname.astext().split(None, 1)
			except ValueError:
				# maybe an argument-less field type?
				fieldtype, fieldarg = fieldname.astext(), ''
			typedesc, is_typefield = typemap.get(fieldtype, (None, None))

			# sort out unknown fields
			if typedesc is None or typedesc.has_arg != bool(fieldarg):
				# either the field name is unknown, or the argument doesn't
				# match the spec; capitalize field name and be done with it
				new_fieldname = fieldtype[0:1].upper() + fieldtype[1:]
				if fieldarg:
					new_fieldname += ' ' + fieldarg
				fieldname[0] = nodes.Text(new_fieldname)
				entries.append(field)
				# debug("APPENDIX", "3", typedesc, field)
				continue

			typename = typedesc.name

			# collect the content, trying not to keep unnecessary paragraphs
			if _is_single_paragraph(fieldbody):
				content = fieldbody.children[0].children
			else:
				content = fieldbody.children

			# if the field specifies a type, put it in the types collection
			if is_typefield:
				# filter out only inline nodes; others will result in invalid
				# markup being written out
				content = [n for n in content if isinstance(n, nodes.Inline) or isinstance(n, nodes.Text)]
				if content:
					types.setdefault(typename, {})[fieldarg] = content
				continue

			# also support syntax like ``:param type name:``
			if typedesc.is_typed:
				try:
					argtype, _ = fieldarg.split(None, 1)  # _ was 'argname' but it is presently unused
				except ValueError:
					pass
				else:
					types.setdefault(typename, {})[fieldarg] = [nodes.Text(argtype)]

			translatable_content = nodes.inline(fieldbody.rawsource, translatable=True)
			translatable_content.source = fieldbody.parent.source
			translatable_content.line = fieldbody.parent.line
			translatable_content += content

			# grouped entries need to be collected in one entry, while others get one entry per field
			if typedesc.is_grouped:
				if typename in groupindices:
					group = entries[groupindices[typename]]
				else:
					groupindices[typename] = len(entries)
					group = [typedesc, []]
					entries.append(group)
				entry = typedesc.make_entry(fieldarg, [translatable_content])
				group[1].append(entry)
			else:

				entry = typedesc.make_entry(fieldarg, [translatable_content])
				entries.append([typedesc, entry])

		# step 2: all entries are collected, construct the new field list
		new_list = []
		pseudo_field = False
		field_name = None

		for entry in entries:
			if isinstance(entry, nodes.field):
				# pass-through old field
				new_list += entry
				pseudo_field = False
			else:
				fieldtype, content = entry
				field_name = fieldtype.name
				if isinstance(fieldtype, PseudoField):
					pseudo_field = True

				fieldtypes = types.get(fieldtype.name, {})
				new_list.append(fieldtype.make_field(fieldtypes, self.domain, content))
		node.replace_self(new_list if pseudo_field else nodes.field_list("", *new_list, id=field_name))


# two classes below violate normal class naming standard in order to uphold docutils idiomatic naming for node classes.
class semantic_sibling_section(nodes.section):  # pylint: disable=invalid-name
	"""
	Node that stands in for a sub-section, but gets rendered at parents indentation.

	Allows us to nest something like a seealso directive under the element it refers to, but not get another level of indentation tacked on in output.
	"""
	valid_builders = ["html", "plain", "doxygen"]

	@classmethod
	def _scrubbing_bubbles(cls, app, doctree, docname):
		"""Replace semantic_sibling_section nodes with children if builder can't handle them."""
		for semantics in doctree.traverse(semantic_sibling_section):
			semantics.replace_self(semantics.children)

	@classmethod
	def _scrub(cls, app, doctree, docname):
		"""Check builder and replace with appropriate scrub function."""

		# builder doesn't change w/in run; we only need to check once
		if app.builder.name in cls.valid_builders:
			cls._scrub = lambda x, y, z: None
		else:
			cls._scrub = cls._scrubbing_bubbles
			cls._scrubbing_bubbles(app, doctree, docname)


# node
class lpc_see_also(addnodes.seealso):  # pylint: disable=invalid-name
	"""
	Custom seealso class enables the output builders to treat "our" seealso differently.

	This enables custom visual style for our (top-level) see-also style, but use default style for a seealso nested under a specific subtopic.
	"""
	pass


# TODO: refactor to base this on some quality/capability, not  identity
class PseudoField(object):
	"""
	Enables our docfield transformer to tell our fields apart from stock.

	This lets us pass stock fields through untouched.
	"""
	pass

# TypedField args: name, names=(), typenames=(), label=None, rolename=None, typerolename=None, can_collapse=False
# GroupedField args: name, names=(), label=None, rolename=None, can_collapse=False

TYPEUNION_SPLIT_RE = re.compile("[<>|*]")  # TODO: should this be in use?


# TODO: rename this if nothing else uses it.
class LPCTypedField(TypedField):
	"""New TypedField base to add LPC-specific type handling for documenting args."""
	TYPEUNION_PUNCT = ["<", "|", ">"]

	# VERBATIM FROM sphinx.util.docfields.TypedField unless otherwise noted
	def make_field(self, types, domain, items):
		def handle_item(fieldarg, content):
			par = nodes.paragraph()
			par += self.make_xref(
				self.rolename,
				domain,
				fieldarg.split()[-1],  # differ +: .split()[-1]
				addnodes.literal_strong
			)
			if fieldarg in types:
				par += nodes.Text(' (')
				fieldtype = types.get(fieldarg)  # differ: get->pop
				if len(fieldtype) == 1 and isinstance(fieldtype[0], nodes.Text):
					typename = u''.join(n.astext() for n in fieldtype)
					# start all lines differ
					token = []
					for char in typename:
						if char not in self.TYPEUNION_PUNCT:
							token.append(char)
						else:
							if len(token):
								par += self.make_xref(self.typerolename, domain, "".join(token), addnodes.literal_emphasis)
								token = []
							par += nodes.Text(char, char)

					if len(token):
						par += self.make_xref(self.typerolename, domain, "".join(token), addnodes.literal_emphasis)
					# end all lines differ
				else:
					par += fieldtype
				par += nodes.Text(')')
			par += nodes.Text(' -- ')
			par += content
			return par

		fieldname = nodes.field_name('', self.label)
		if len(items) == 1 and self.can_collapse:
			fieldarg, content = items[0]
			bodynode = handle_item(fieldarg, content)
		else:
			bodynode = self.list_type()
			for fieldarg, content in items:
				bodynode += nodes.list_item('', handle_item(fieldarg, content))
		fieldbody = nodes.field_body('', bodynode, id=self.name)
		return nodes.field('', fieldname, fieldbody)
	# END VERBATIM


class LPCHistoryField(TypedField, PseudoField):
	"""Enables using ":history <version> <status>: <message>" docfield markup."""
	tagname = "history"
	cap_tag = tagname.upper()

	def make_field(self, types, domain, items):
		node = semantic_sibling_section(ids=[self.cap_tag])  # TODO: correct IDs?
		node.tagname = self.tagname

		# VERBATIM FROM sphinx.util.docfields.TypedField unless otherwise noted
		def handle_item(fieldarg, content):
			par = nodes.paragraph()
			par += self.make_xref(self.rolename, domain, fieldarg.split()[-1], addnodes.literal_strong)  # differ +: .split()[-1]
			if fieldarg in types:
				par += nodes.Text(' (')
				# NOTE: using .pop() here to prevent a single type node to be inserted twice into the doctree, which leads to inconsistencies later when references are resolved
				fieldtype = types.pop(fieldarg)
				if len(fieldtype) == 1 and isinstance(fieldtype[0], nodes.Text):
					typename = u''.join(n.astext() for n in fieldtype)
					# TODO: below differs by not using make_xref again; make_xref would turn our type (or <version> in LPCHistoryField terms) into a reference. We could certainly make this a link of some sort, but for now there's no obvious place to link it. We don't maintain changenotes with this level of granularity. Perhaps we could link to something on the bugtracker or github?
					par += addnodes.literal_emphasis(typename, typename)
				else:
					par += fieldtype
				par += nodes.Text(')')
			if len(content[0]):
				par += nodes.Text(' -- ')
				par += content
			return par

		title = nodes.title('', self.label)  # differs: field_name -> title
		title.tagname = self.tagname  # differs: line added
		node += title  # differs: line added
		if len(items) == 1 and self.can_collapse:
			fieldarg, content = items[0]
			bodynode = handle_item(fieldarg, content)
		else:
			bodynode = self.list_type()
			for fieldarg, content in items:
				bodynode += nodes.list_item('', handle_item(fieldarg, content))
		node += bodynode  # differs significantly
		return node  # differs significantly
	# END VERBATIM

# # # Declare our custom admonitions  # # #
admonitionlabels["security"] = l_('Security')
admonitionlabels["limit"] = l_('Limit')
admonitionlabels["stability"] = l_('Stability')
admonitionlabels["obsolete"] = l_('Obsolete')
admonitionlabels["misleading"] = l_('Misleading')


# again following docutils naming idiom
class security(nodes.warning):  # pylint: disable=invalid-name
	pass


class limit(nodes.warning):  # pylint: disable=invalid-name
	pass


class stability(nodes.warning):  # pylint: disable=invalid-name
	pass


class obsolete(nodes.warning):  # pylint: disable=invalid-name
	pass


class misleading(nodes.warning):  # pylint: disable=invalid-name
	pass


class LPCSecurityWarning(directives.admonitions.Warning):
	node_class = security


class LPCLimitWarning(directives.admonitions.Warning):
	node_class = limit


class LPCStabilityWarning(directives.admonitions.Warning):
	node_class = stability


class LPCObsoleteWarning(directives.admonitions.Warning):
	node_class = obsolete


class LPCMisleadingWarning(directives.admonitions.Warning):
	node_class = misleading


class LPCObject(c.CObject):
	"""Base directive class for LPC-specific directives."""
	status_options = ["optional", "deprecated", "obsolete", "preliminary", "experimental"]
	synopsis_title = "SYNOPSIS"
	doc_field_types = c.CObject.doc_field_types + [
		LPCHistoryField(
			'history',
			label=l_('History'),
			names=('history', 'introduced'),
			typerolename='version',
			typenames=('version',)
		),
	]
	__base__ = None  # assigned when our DirectiveAdapter class is created in LPCDomain.directive

	# Sphinx uses these a lot but never declares them; just atoning for their sins
	objtype = domain = indexnode = names = env = None

	option_spec = {
		# document status
		"optional": lambda x: "OPTIONAL",
		"deprecated": lambda x: "DEPRECATED",
		"preliminary": lambda x: "PRELIMINARY",
		"obsolete": lambda x: "OBSOLETE",
		"removed": lambda x: "REMOVED",
		"experimental": lambda x: "EXPERIMENTAL",
		# other things
		"synopsis": directives.unchanged,
		"include": directives.unchanged,
		"topic": directives.unchanged  # add to this index?
	}
	option_spec.update(c.CObject.option_spec)
	csplit_re = re.compile(r',\s*')

	@property
	def tagname(self):
		"""Return the name of the present tag."""
		# this looks convoluted because Sphinx injects an adapter class that otherwise obscures our tagname, so we have to use a workaround to find it. See 'directive' method on LPCDomain for more.
		return self.__base__.__name__.lower()[3:]

	@property
	def noindex(self):
		return 'noindex' in self.options

	def get_status_desc(self):
		"""Return comma-delimited list of valid status options or empty string."""
		optiondesc = ", ".join([self.options[x] for x in self.options if x in self.status_options])
		return " (%s)" % optiondesc if len(optiondesc) else ""

	def _parse_node_meta(self, out_node):
		# this transfers the domain from the directive to the node itself, allowing for the node to retain a sense of originary domain later... for now I'm just going to be really wreckless and move all of these to the same node...
		out_node['domain'] = self.domain
		# 'desctype' is a backwards compatible attribute
		out_node['objtype'] = out_node['desctype'] = self.objtype
		out_node['noindex'] = self.noindex  # TODO: not in scope
		out_node.document = self.state.document
		out_node.tagname = self.tagname
		out_node.line = self.lineno
		# TODO: am I respecting what noindex does? Do we need it? Can we just cut it altogether?

	def _parse_meta(self, out_node=None):
		if ':' in self.name:
			self.domain, self.objtype = self.name.split(':', 1)
		else:
			self.domain, self.objtype = '', self.name
		self.env = self.state.document.settings.env
		self.names = []

		if out_node:
			self._parse_node_meta(out_node)

		# TODO: given below note, this may be pointless since we aren't planning on using the directive form, I don't think; let's disable it and see what breaks.
		if self.names:
			# needed for association of version{added,changed} directives
			self.env.temp_data['object'] = self.names[0]

	def _parse_type(self, attach_to, ctype):  # pylint: disable=unused-argument
		# add cross-ref nodes for all words
		for part in [_f for _f in c.wsplit_re.split(ctype) if _f]:
			tnode = nodes.Text(part, part)
			if part[0] in string.ascii_letters + '_' and part not in self.stopwords:
				pnode = addnodes.pending_xref(
					'', refdomain='lpc', reftype='type', reftarget=part, modname=None, classname=None, refdoc=self.env.docname)
				pnode += tnode
				attach_to += pnode
			else:
				attach_to += tnode

	def get_includes(self):
		return self.options["include"].split("\n") if "include" in self.options else []

	def _parse_includes(self, signodes):
		for incl in self.get_includes():
			inclnode = addnodes.desc_signature("", "#include %s" % incl)
			inclnode['objtype'] = "include"
			signodes.append(inclnode)

	def get_synopsis_node(self):
		synopsis = nodes.section(ids=[self.synopsis_title])  # TODO: fix ids
		synopsis += nodes.title(text=self.synopsis_title + self.get_status_desc())
		return synopsis

	def _parse_synopsis_syntax(self, synopsis_node, out_node):  # pylint: disable=unused-argument
		if "synopsis" in self.options:
			synopsis_node += nodes.field_list('',
				nodes.field('',
					nodes.field_name(self.arguments[0], self.arguments[0]),
					nodes.field_body("", nodes.inline("", self.options["synopsis"]))
				)
			)
		else:
			synopsis_node += nodes.paragraph("", "", nodes.Text(self.arguments[0], self.arguments[0]))

	def _parse_synopsis(self, out_node):
		synopsis_node = self.get_synopsis_node()

		self._parse_synopsis_syntax(synopsis_node, out_node)

		out_node += synopsis_node

	def get_content_node(self):  # pylint: disable=no-self-use
		"""Return the node the directive's primary content should be attached to."""
		content = nodes.section(ids=["DESCRIPTION"])  # TODO: IDs
		content += nodes.title(text="DESCRIPTION")
		return content

	def _parse_content(self, out_node):  # pylint: disable=unused-argument
		"""
		Parse directive content and attach it to out_node.

		The default steps in this process are:
		- call an overridable method to get the primary node to which the directive's 'content' will be attached.
		- call an sphinx/docutils before_content method used to prepare to parse content.
		- call the RST parser with the directive's 'content' and our content node; the parser will create child nodes from the output and attach them for us (if we don't perform this step, any 'content' nested under this directive is lost).
		- use the docfield transformer to further extract/parse docfields out of the parsed content.
		- """
		cont_node = self.get_content_node()

		out_node += cont_node

		self.before_content()
		self.state.nested_parse(self.content, self.content_offset, cont_node)
		LPCDocFieldTransformer(self).transform_all(cont_node)
		self.env.temp_data['object'] = None  # TODO: this value is set in _parse_meta, and may be going away...
		self.after_content()

	def get_index_text(self, name):
		return "{name}({kind})".format(kind=self.objtype, name=name)

	def get_topics(self):
		if "topic" in self.options:
			return self.csplit_re.split(self.options["topic"])
		return []

	def add_target(self, name, signode):
		set_source_info(self, signode)
		targetname = 'lpc.' + name

		if targetname not in self.state.document.ids:
			signode['names'].append(targetname)
			signode['ids'].append(targetname)
			signode['first'] = (not self.names)
			self.state.document.note_explicit_target(signode)

			try:
				inv = self.env.domaindata['lpc'][self.objtype]
			except KeyError:
				inv = self.env.domaindata['lpc']['objects']

			# TODO: this *can* warn us even if it's in the same location, because it's checking in a location that is cached/pickled from the previous run; if this doc was parsed previously, we'll get a spurious warning (er, what did this mean?)
			target_tuple = (self.env.docname, self.objtype)

			if name in inv:
				if target_tuple == inv[name]:
					# this is probably safe; it's in the same file
					# TODO: the risk is only if you redefine the same object in the same file (is this plausible enough to bother with?) perhaps this one becomes the warning, and the other becomes an error?
					pass
				else:
					# different location
					self.state_machine.reporter.warning(
						'duplicate LPC object description of %s, ' % name + 'other instance in ' + self.env.doc2path(inv[name][0]), line=self.lineno)
			else:
				# we differ from core sphinx domains here; most of them would overwrite this and let the last prevail, but we're going to keep the first (all of the errant ones get documented by the warning and are thus the ones that should be "lost"; if we discard the first--the one that never gets explicitly documented as a duplicate--we'll have to go hunting to figure out where it is.)
				inv[name] = target_tuple

		return targetname

	def add_index(self, targetname, name):
		indextext = self.get_index_text(name)
		if indextext:
			self.indexnode['entries'].append(('single', indextext, targetname, ''))
			self.indexnode['entries'].append(('single', self.objtype + "; " + indextext, targetname, ''))
			for topic in self.get_topics():
				self.indexnode['entries'].append(('single', topic + "; " + indextext, targetname, ''))

	def add_target_and_index(self, name, sig, signode):
		self.add_index(self.add_target(name, signode), name)

	def get_out_node(self):  # pylint: disable=no-self-use
		"""Returns the node that will represent this directive, to which all of its other output will be attached."""
		return nodes.section(ids=["glossary"])  # TODO: this isn't the right id, at all

	def run(self):
		"""
		Main directive entry function, called by docutils upon encountering the directive.

		Existing code is supposedly easy to subclass, but has much idiomatic that must be turned into copypasta in order to make small changes to the output or document model. Much of this complexity has been factored out into multiple functions. This function now simply:
		- creates an index node
		- calls an overridable method to get the base 'out_node' which will represent this directive
		- passes the out_node to a series of parse methods which are responsible for attaching whatever child nodes they would like to the out_node: _parse_meta, _parse_synopsis, _parse_content
		- returns a list containing the index node and the out node

		See the factored-out parsing functions for more on their purpose and using/overriding them.
		"""
		self.indexnode = addnodes.index(entries=[])
		out_node = self.get_out_node()
		self._parse_meta(out_node)

		self._parse_synopsis(out_node)
		self._parse_content(out_node)

		return [self.indexnode, out_node]


class LPCGlossary(LPCObject, sphinx.domains.std.Glossary):
	optional_arguments = 1
	required_arguments = 0
	final_argument_whitespace = True

	# TODO: integrate with LPCObject parse model...
	def _parse_content(self, out_node):
		title = self.arguments[0].strip() if len(self.arguments) else None
		if title and len(title):
			out_node += nodes.title(text=title.upper())
			out_node['ids'] = [title]

		if 'synopsis' in self.options:
			out_node += nodes.paragraph(text=self.options['synopsis'])

		original = sphinx.domains.std.Glossary.run(self)
		# sphinx applies a glossary class here, which they style in a specific way that makes each term very bold; let's take another swing at it.
		original[-1][0]["classes"].remove("glossary")
		out_node += original

	def run(self):
		out_node = self.get_out_node()
		self._parse_meta(out_node)
		self._parse_content(out_node)
		return [out_node]  # TODO: was this a temp thing that worked right, or that should be rolled back?
		return [self.indexnode, out_node]


# directive
class LPCSeeAlso(LPCObject):
	node_class = lpc_see_also
	required_arguments = 1

	# TODO: rm unused var
	def run(self):
		# current_depth = 0
		most_parent = self.state.parent
		while most_parent.parent:
			# current_depth += 1
			most_parent = most_parent.parent

		contentnode = None
		if isinstance(most_parent, nodes.section):
			contentnode = semantic_sibling_section(ids=['see2also'])  # TODO: ids
			see_aslan = nodes.title(text="SEE ALSO")
			see_aslan.tagname = "seealso"
			contentnode += see_aslan
			contentnode += nodes.paragraph("", "", *self.state.inline_text(self.arguments[0], self.lineno)[0])

		else:
			contentnode = nodes.field_list(
				"",
				nodes.field(
					"",
					nodes.field_name(
						"",
						"See Also"
					),
					nodes.field_body(
						"",
						nodes.paragraph("", "", *self.state.inline_text(self.arguments[0], self.lineno)[0])
					)
				)
			)
		contentnode.tagname = "seealso"
		return [contentnode]


class LPCVar(LPCObject):
	"""Conceptually similar to LPCObject, but for smaller things (i.e., no separate sections). Could use a more generic/re-usable name."""

	varnames = []

	def get_out_node(self):
		return nodes.definition_list_item(ids=self.varnames)  # TODO: ids?

	def get_synopsis_node(self):
		return nodes.term("", ", ".join(self.varnames))

	def _parse_synopsis_syntax(self, synopsis_node, out_node):
		for var in self.varnames:
			# debug("TRYING TO ADD", var)
			self.add_target_and_index(var, None, synopsis_node)
			break

	def get_content_node(self):
		return nodes.definition()

	def run(self):
		self.varnames = self.arguments[0].splitlines()
		indexnode, out_node = super().run()
		return [indexnode, nodes.definition_list("", out_node)]


# TODO: light-weight way to generate these?
class LPCUsage(LPCObject):
	required_arguments = 0

	def run(self):
		temp = nodes.section(ids=["USAGE"])
		temp.tagname = "usage"
		temp += nodes.title(text="USAGE")
		self.state.nested_parse(self.content, self.content_offset, temp)
		return [temp]


class LPCLore(LPCObject):
	required_arguments = 0

	def run(self):
		temp = semantic_sibling_section(ids=["LORE"])  # TODO: ids
		temp += nodes.title(text="LORE")
		self.state.nested_parse(self.content, self.content_offset, temp)
		return [temp]


class LPCFunction(LPCObject):
	doc_field_types = [
		LPCHistoryField(
			'history',
			label=l_('HISTORY'),
			names=('history', 'introduced'),
			typerolename='version',
			typenames=('version',)
		),
		LPCTypedField(
			'arguments',
			label=l_('Arguments'),
			names=('arg', 'argument'),
			typerolename='type',
			typenames=('type',)
		),
	]
	# stopwords are used to avoid linking something like a type if there's nowhere for it to link; hopefully ours can all have targets
	stopwords = set()
	comment_match = r'(?:/\*|//)\s*(.*?)\s*(?:\*/)?\s*$'

	def handle_signature(self, sig, signode):
		temp = re.split(self.comment_match, sig)
		# TODO: maybe do something different here for sig lines that are *all* comment
		sig = temp[0].strip()
		if len(temp) > 1:
			comment = temp[1].strip()
			signode += addnodes.desc_annotation(comment, comment)
		return None, super().handle_signature(sig, signode)

	def get_out_node(self):
		"""Override to set no id; we'll set it later/conditionally in the parse."""
		return nodes.section()

	def get_title(self, name):
		return CrouchingTitle(text="{0}::{1}()".format(self.objtype, name))


	def _parse_synopsis_syntax(self, synopsis_node, out_node):
		"""Parse synopsis into a set of synopsis nodes, which should get appended to the parent synopsis_node."""

		signatures = self.get_signatures()
		signodes = []

		self._parse_includes(signodes)

		for sig in signatures:
			# add a signature node for each signature in the current unit and add a reference target for it
			signode = addnodes.desc_signature(sig, '')
			signode['first'] = False
			signodes.append(signode)
			try:
				# name can also be a tuple, e.g. (classname, objname);
				# this is strictly domain-specific (i.e. no assumptions may be made in this base class)
				docname, signame = self.handle_signature(sig, signode)
			except ValueError:
				signode.clear()
				signode += addnodes.desc_name(sig, sig)
				continue  # we don't want an index entry here

			# TODO: really close to being able to decompose these into a single function, but the slight difference at the end of each makes it tricky. priority not high enough to spend more time on it for now
			if docname and docname not in self.names:
				synopsis_node["ids"].append(docname)  # need the funcname
				# out_node += CrouchingTitle(text=docname)
				out_node += self.get_title(signame)
				self.names.append(docname)
				if not self.noindex:
					# only add target and index entry if this is the first
					# description of the object with this name in this desc block
					if docname == signame:
						self.add_target_and_index(signame, sig, signode)
					else:
						self.add_target(docname, out_node)

			if signame not in self.names:
				synopsis_node["ids"].append(signame)  # need the funcname
				out_node += self.get_title(signame)
				self.names.append(signame)
				if not self.noindex:
					# only add target and index entry if this is the first description of the object with this name in this desc block
					self.add_target_and_index(signame, sig, signode)

		signodes += addnodes.desc_content(children=nodes.paragraph("<value> being:", "<value> being:"))
		# pull out in-synopsis params? or just do it normally?

		node = addnodes.desc("", *signodes, desctype="function", domain="lpc", objtype="function")  # TODO: get at least the domain from the proper location?

		synopsis_node += node

	# TODO: if 'names' can be added before or after this code, this could easily add names and just call super()._parse_synopsis(out_node); everything else is the same.
	def _parse_synopsis(self, out_node):

		synopsis = self.get_synopsis_node()

		self.names = []

		self._parse_synopsis_syntax(synopsis, out_node)

		out_node += synopsis

	def _parse_meta(self, out_node=None):
		super()._parse_meta(out_node)


# TODO: is there a better way to do this?
class LPCHookIndex(Index):  # pylint: disable=too-few-public-methods
	name = "hookindex"
	localname = "localhookindex"
	shortname = "shorthookindex"

	def generate(self, docnames=None):
		collapse = False
		content = []
		last_letter = None

		for hook_name in sorted(self.domain.data['hook'], key=str.lower):
			name = hook_name
			docname, anchor = self.domain.data['hook'][hook_name]
			entries = [name, 0, docname, anchor, 'extra', 'qualifier', 'descr']
			letter = name[0]

			if letter == last_letter:
				content[-1][1].append(entries)
			else:
				content.append((letter, [entries]))

			last_letter = letter
		return (content, collapse)


class LPCHook(LPCFunction):
	def handle_signature(self, sig, signode):
		signode += addnodes.desc_name("set_driver_hook", "set_driver_hook")
		paramlist = addnodes.desc_parameterlist()
		signode += paramlist
		paramlist += addnodes.desc_parameter(sig, sig)
		paramlist += addnodes.desc_parameter("value", "value")
		return self.env.docname.rsplit("/")[-1], sig

	def get_includes(self):
		return ["<sys/driver_hooks.h>"] + super().get_includes()

	def get_title(self, name):
		return CrouchingTitle(text=name)


class LPCApplied(LPCFunction):
	def handle_signature(self, sig, signode):
		oldtype = self.objtype
		self.objtype = "function"
		ret = (
			self.env.docname.rsplit("/")[-1],
			super().handle_signature(sig, signode)[-1]
		)
		self.objtype = oldtype
		return ret


class LPCSubtopic(LPCObject):
	# letting this one repeat a little it uses the same basic code, but it shifts the attachment locus by a node for most of these, which will be more clear if it's handled in one function instead of magicked through multiple overrides.

	def _parse_content(self, out_node):
		out_node += nodes.title(text=self.arguments[0].upper())

		# TODO: I think disabling these is right, but this may break something re: targeting and may throw a wrench in the works...
		# self.names = []
		# self.add_target(self.arguments[0], out_node)

		self.before_content()
		self.state.nested_parse(self.content, self.content_offset, out_node)
		LPCDocFieldTransformer(self).transform_all(out_node)
		self.env.temp_data['object'] = None
		self.after_content()

	# let's not, actually :]
	def _parse_synopsis(self, out_node):
		pass


class LPCTopic(LPCObject):
	doc_field_types = c.CObject.doc_field_types + [
		LPCHistoryField(
			'history',
			label=l_('HISTORY'),
			names=('history', 'introduced'),
			typerolename='version',
			typenames=('version',)
		),
	]
	required_arguments = 1

	def __init__(self, *arg, **kwarg):
		super().__init__(*arg, **kwarg)
		self.synopsis_title = self.name.upper()

	def get_out_node(self):
		topic = nodes.section(ids=[self.arguments[0]])
		topic += CrouchingTitle(text=self.arguments[0])
		return topic

	def run(self):
		temp = super().run()
		self.add_target_and_index(self.arguments[0], None, temp[1])
		return temp


class LPCCommand(LPCTopic):

	# commands can have multiple forms; don't want all of them as the title
	def get_out_node(self):
		topic = nodes.section(ids=[self.arguments[0]])
		topic += CrouchingTitle(text=self.arguments[0].split()[0])
		return topic


class LPCType(LPCTopic):
	pass


class LPCXRefRole(c.CXRefRole):
	pass


class LPCGuide(LPCTopic):
	# def _parse_synopsis(self, attach_to):
	# 	pass

	# this used "INTRODUCTION" but I've rolled it back to "DESCRIPTION" for now
	def get_content_node(self):
		intro = nodes.section(ids=["DESCRIPTION"])  # TODO: fix ids
		intro += nodes.title(text="DESCRIPTION")
		return intro


# TODO: probably a better way to handle
class LPCLang(LPCTopic):
	required_arguments = 1  # TODO: why?


class LPCSyntax(LPCLang):
	synopsis_title = "SYNTAX"

	def _parse_synopsis_syntax(self, synopsis_node, out_node):
		synopsis_node += self.parse_syntax(self.arguments[0].splitlines()[1:])

	def parse_syntax(self, lines):  # pylint: disable=no-self-use
		syntax = u'\n'.join(lines)
		return nodes.literal_block(syntax, syntax)


# note: we declare some generic objects and some specific objects based on those in object_types, directives and roles below; the specific types are listed under the generic type (with an extra indent) in order to suggest these relationships
# TODO: either undo above, or re-eval for correctness; this has all evolved a lot
class LPCDomain(c.CDomain):
	name = 'lpc'
	label = 'LPC'

	# TODO: figure out what this is for (i.e., resolve the nagging concern I have stomped all over its purpose; I know it's for localization, roughly, just not sure on specifics)
	object_types = {
		'topic': ObjType(l_('topic'), 'topic'),
			'concept': ObjType(l_('concept'), 'concept'),
			'driver': ObjType(l_('driver'), 'driver'),
			'directory': ObjType(l_('directory'), 'directory'),
		'function': ObjType(l_('function'), 'function'),
			'applied': ObjType(l_('applied'), 'applied'),
			'efun': ObjType(l_('efun'), 'efun'),
			'hook': ObjType(l_('hook'), 'hook'),
			'master': ObjType(l_('master'), 'master'),
			# 'obsolete': ObjType(l_('obsolete'), 'obsolete'),
		# 'guide': ObjType(l_('guide'), 'guide'),
		# 	'internal': ObjType(l_('internal'), 'internal'),
		# 	'tutorial': ObjType(l_('tutorial'), 'tutorial'),
		'lang': ObjType(l_('lang'), 'lang'),
			'syntax': ObjType(l_('syntax'), 'syntax'),
				'keyword': ObjType(l_('keyword'), 'keyword'),
					'modifier': ObjType(l_('modifier'), 'modifier'),
					'type': ObjType(l_('type'), 'type'),
				'operator': ObjType(l_('operator'), 'operator'),
			'pragma': ObjType(l_('pragma'), 'pragma'),
		'command': ObjType(l_('command'), 'command'),
		'macro': ObjType(l_('macro'), 'macro'),
		'seealso': ObjType(l_('seealso'), 'seealso'),
		'subtopic': ObjType(l_('subtopic'), 'subtopic'),
		'usage': ObjType(l_('usage'), 'usage'),
		'var': ObjType(l_('variable'), 'data'),
		'enumerate': ObjType(l_('enumerate'), 'enumerate'),
		'meta': ObjType(l_('meta'), 'meta'),
	}

	directives = {
		'topic': LPCTopic,
			'concept': LPCTopic,
			'driver': LPCTopic,
			'directory': LPCTopic,
		'lang': LPCLang,
			'syntax': LPCSyntax,
				'keyword': LPCSyntax,
					'modifier': LPCVar,
					'type': LPCType,
				'operator': LPCSyntax,
			'pragma': LPCVar,
		'function': LPCFunction,
			'applied': LPCApplied,
			'efun': LPCFunction,
			'hook': LPCHook,
			'master': LPCFunction,
			# 'obsolete': LPCFunction,
		'guide': LPCGuide,
			# 'internal': LPCGuide,
			# 'tutorial': LPCGuide,?
		'command': LPCCommand,

		'macro': LPCVar,
		# 'object': LPCObject,
		'seealso': LPCSeeAlso,
		'subtopic': LPCSubtopic,
		'usage': LPCUsage,
		'lore': LPCLore,
		'var': LPCObject,
		'enumerate': LPCGlossary,
		'meta': LPCTopic,
	}
	roles = {
		'topic': LPCXRefRole(),  # innernodeclass=nodes.strong),
			'concept': LPCXRefRole(),  # innernodeclass=nodes.inline),
			'driver': LPCXRefRole(),
			'directory': LPCXRefRole(),
		'lang': LPCXRefRole(),  # innernodeclass=nodes.inline),
			'syntax': LPCXRefRole(),
				'keyword': LPCXRefRole(),
					'modifier': LPCXRefRole(),
					'type': LPCXRefRole(),
				'operator': LPCXRefRole(),
			'pragma': LPCXRefRole(),
		'function': LPCXRefRole(fix_parens=True),
			'applied': LPCXRefRole(),
			'efun': LPCXRefRole(fix_parens=True),
			'hook': LPCXRefRole(),
			'master': LPCXRefRole(),
			'obsolete': LPCXRefRole(),
		'guide': LPCXRefRole(),
			'internal': LPCXRefRole(),
		'command': LPCXRefRole(),
		'macro': LPCXRefRole(),
		'usage': LPCXRefRole(),
		'var': LPCXRefRole(),
		'enumerate': LPCXRefRole(),  # TODO: do we ever practically need this?
		'meta': LPCXRefRole(),
	}
	# TODO: when doc-set is mostly complete, drop in some test code that flags any of these that are empty at the end of a full parse run (subtext: they probably aren't necessary)
	initial_data = {
		"applied": {},
		"command": {},
		"concept": {},
		"directory": {},
		"driver": {},
		"enumerate": {},  # TODO: needed? presently no entries
		"glossary": {},  # TODO: needed? presently no entries (esp given above?)
		"meta": {},
		"hook": {},
		"macro": {},
		"master": {},
		"objects": {},
		'lang': {},
			'syntax': {},
				'keyword': {},
					'modifier': {},
					'type': {},
				'operator': {},
			'pragma': {},
		'var': {},  # TODO: needed? presently no entries
	}
	indices = [LPCHookIndex]  # TODO: eval whether we still need this hookindex, whether we're using it, and whether we need some other kinds of index that we don't have already; keeping it for now, just so we have an example of a separate index and how to make one; AFAIK nothing links directly to this atm

	def directive(self, directive_name):
		"""Overload the default directive handling to store the original directive for later access."""
		# all but 1 line is copy-pasta from sphinx/directives/__init__.py
		if directive_name in self._directive_cache:
			return self._directive_cache[directive_name]
		if directive_name not in self.directives:
			return None
		fullname = '%s:%s' % (self.name, directive_name)
		BaseDirective = self.directives[directive_name]  # pylint: disable=invalid-name

		class DirectiveAdapter(BaseDirective):  # pylint: disable=no-init
			name = None
			__base__ = BaseDirective  # this is our only edit; save a copy of BaseDirective

			def run(self):
				self.name = fullname
				return BaseDirective.run(self)

		self._directive_cache[directive_name] = DirectiveAdapter
		return DirectiveAdapter

	def resolve_xref(self, env, fromdocname, builder, typ, target, node, contnode):  # pylint: disable=too-many-arguments
		"""Return a resolved refnode or none."""

		DEV_REF > 1 and debug("DEV_REF: attempting to resolve xref",
			{"env": env},
			{"fromdocname": fromdocname},
			{"builder": builder},
			{"typ": typ},
			{"target": target},
			{"node": node, "refdomain": node['refdomain'] if 'refdomain' in node else None},
			{"contnode": contnode}
		)
		# strip pointer asterisk
		target = target.rstrip(' *')

		if typ in self.directives and typ in self.data and target in self.data[typ]:
			# typ already set to something useful
			pass
		elif target in self.data["objects"]:
			# or the target was in our fallback 'objects'
			typ = "objects"
		else:
			return None
		obj = self.data[typ][target]

		refnode = make_refnode(builder, fromdocname, obj[0], 'lpc.' + target, contnode, target)
		refnode['section'] = obj[1]
		refnode['fromdoc'] = fromdocname
		refnode['todoc'] = obj[0]
		DEV_REF > 1 and debug("DEV_REF: resolved xref to",
			{"obj": obj},
			{"obj[0]": obj[0]},
			{"obj[1]": obj[1]},
			{"target": target},
			{"contnode": contnode},
			{"refnode": refnode}
		)
		return refnode

	# for reference, make_refnode synopsis:
	# make_refnode(builder, from_doc_name, to_doc_name, targetid, child, title=None):

	def resolve_any_xref(self, env, fromdocname, builder, target, node, contnode):  # pylint: disable=too-many-arguments
		"""Resolve and return a sensible refnode for an 'any' ref if possible, otherwise return an empty list."""
		DEV_REF > 1 and debug("DEV_REF: attempting to resolve 'any' xref",
			{"env": env},
			{"fromdocname": fromdocname},
			{"builder": builder},
			{"target": target},
			{"node": node, "refdomain": node['refdomain'] if 'refdomain' in node else None},
			{"contnode": contnode}
		)
		# strip pointer asterisk
		target = target.rstrip(' *')

		# TODO: list of refs we'll bother identifyin without providing the type; this could be liberal for easy references, or very tightly controlled to require doc source be more semantic
		for typ in ["concept", "efun", "hook", "master", "lang", "objects"]:
			if typ in self.data and target in self.data[typ]:
				obj = self.data[typ][target]
				refnode = make_refnode(builder, fromdocname, obj[0], 'lpc.' + target, contnode, target)
				refnode['section'] = obj[1]
				DEV_REF > 1 and debug(
					"DEV_REF: resolved any_xref to",
					{"obj": obj},
					{"obj[0]": obj[0]},
					{"obj[1]": obj[1]},
					{"target": target},
					{"contnode": contnode},
					{"refnode": refnode}
				)
				return [('lpc:' + self.role_for_objtype(obj[1]), refnode)]

		return []


class LPCAppliedDomain(LPCDomain):
	name = 'applied'
	label = 'applied'


# TODO: For organizational clarity it might be useful to factor a few of the bigger sections, such as the desc functions, out into a mixin
# docutils uses two catch-all functions for raising errors on unimplemented visit/depart; pylint likes to complain, but we shouldn't implement them  # pylint: disable=abstract-method
class LPCHTMLTranslator(SmartyPantsHTMLTranslator):  # pylint: disable=abstract-method
	# pylint: disable=unused-argument
	SECTIONS = {
		'applied': 'A',
		# note "concept" (directive) here but "concepts" (directory) in plaintext translator
		'concept': 'C',
		'driver': 'D',
		'efun': 'E',  # how to handle efun.de?
		'hook': 'H',
		'lang': 'LPC',
		'master': 'M',
		# these probably don't work quite the same?
		# ideally obsolete/O works more like, I reference an efun which is defined with an :obsolete: option and so it gets flagged differently and given its own letter, or maybe even something better.
		# 'obsolete': 'O',
		# 'other': 'OTHER',
	}

	def visit_semantic_sibling_section(self, node):
		self.body.append(
			self.starttag(node, 'div', CLASS='section'))

	def depart_semantic_sibling_section(self, node):
		self.body.append('</div>\n')

	def depart_reference(self, node):
		"""Intervene to add a letter representing the 'type' for most references."""
		sect = self.SECTIONS.get(node.get("section"))
		DEV_REF and debug(
			"DEV_REF: html",
			{"node": node},
			{"refid": node.get("refid")},
			{"reftitle": node.get("reftitle")},
			{"refuri": node.get("refuri")},
			{"section": node.get("section")},
		)
		if sect:
			self.body.append("(%s)" % sect)
		return super().depart_reference(node)

	# the following functions support our HTML-based override of how function synopses work and are presented in the html output, which we accomplish by tabling everything so that all elements line up. These are just a bunch of decorator functions so that we can easily flag the many synopsis functions to receive table, tr, or td tags.

	tabling = None

	# pylint: disable=not-callable, no-self-argument
	def start_table(func):
		def wrap_node(self, node):
			self.tabling = True
			if "objtype" in node and node["objtype"] == "function":
				# border-spacing so function-call braces end properly
				self.body.append(self.starttag(node, 'table', CLASS=node['objtype'], style="border-spacing:0;"))
			elif False:
				self.body.append(self.starttag(node, 'table'))
			else:
				self.tabling = False
			func(self, node)
		return wrap_node

	def end_table(func):
		def wrap_node(self, node):
			func(self, node)

			if self.tabling:
				self.body.append('</table>')
			else:
				self.tabling = False
		return wrap_node

	def start_tr(func):
		def wrap_node(self, node):
			if self.tabling:
				self.body.append(self.starttag(node, 'tr'))
			func(self, node)
		return wrap_node

	def end_tr(func):
		def wrap_node(self, node):
			func(self, node)
			if self.tabling:
				self.body.append('</tr>\n')
		return wrap_node

	def start_td(func):
		def wrap_node(self, node):
			if self.tabling:
				self.body.append(self.starttag(node, 'td'))
			func(self, node)
		return wrap_node

	def end_td(func):
		def wrap_node(self, node):
			func(self, node)
			if self.tabling:
				self.body.append('</td>')
		return wrap_node

	def start_th(func):
		def wrap_node(self, node):
			if self.tabling:
				self.body.append(self.starttag(node, 'th'))
			func(self, node)
		return wrap_node

	def end_th(func):
		def wrap_node(self, node):
			func(self, node)
			if self.tabling:
				self.body.append('</th>')
		return wrap_node
	# end table decorator funcs

	# override desc functions to align our
	# desc parts in HTML:
	@start_table
	def visit_desc(self, node):
		if not self.tabling:
			return super().visit_desc(node)

	@end_table
	def depart_desc(self, node):
		if not self.tabling:
			return super().depart_desc(node)

	@start_tr
	def visit_desc_signature(self, node):
		if not self.tabling:
			return super().visit_desc_signature(node)
		# the id is set automatically
		# anchor for per-desc interactive data
		if node.parent.get('objtype') != 'describe' and node['ids'] and node['first']:
			self.body.append('<!--[%s]-->' % node['ids'][0])

	@end_tr
	def depart_desc_signature(self, node):
		if not self.tabling:
			return super().depart_desc_signature(node)
		self.add_permalink_ref(node, _('Permalink to this definition'))

	@start_td
	def visit_desc_addname(self, node):
		if not self.tabling:
			return super().visit_desc_addname(node)
		self.body.append(self.starttag(node, 'code', '', CLASS='descclassname'))

	@end_td
	def depart_desc_addname(self, node):
		if not self.tabling:
			return super().depart_desc_addname(node)
		self.body.append('</code>')

	@start_td
	def visit_desc_type(self, node):
		if not self.tabling:
			return super().visit_desc_type(node)

	@end_td
	def depart_desc_type(self, node):
		if not self.tabling:
			return super().depart_desc_type(node)

	def visit_desc_returns(self, node):
		if not self.tabling:
			return super().visit_desc_returns(node)
		self.body.append(' &rarr; ')

	def depart_desc_returns(self, node):
		if not self.tabling:
			return super().depart_desc_returns(node)

	@start_td
	def visit_desc_name(self, node):
		if not self.tabling:
			return super().visit_desc_name(node)
		self.body.append(self.starttag(node, 'code', '', CLASS='descname'))

	@end_td
	def depart_desc_name(self, node):
		if not self.tabling:
			return super().depart_desc_name(node)
		self.body.append('</code>')

	first_param = None
	required_params_left = None

	def visit_desc_parameterlist(self, node):
		if not self.tabling:
			return super().visit_desc_parameterlist(node)
		self.body.append('<td><span class="sig-paren">(</span></td>')
		self.first_param = 1
		self.optional_param_level = 0
		# How many required parameters are left.
		self.required_params_left = sum([isinstance(c, addnodes.desc_parameter) for c in node.children])
		self.param_separator = node.child_text_separator

	def depart_desc_parameterlist(self, node):
		if not self.tabling:
			return super().depart_desc_parameterlist(node)
		self.body.append('<td colspan="1000" style="border:0;padding:0;margin:0;text-align:right;"><span class="sig-paren">)</span></td>')

	# If required parameters are still to come, then put the comma after
	# the parameter.  Otherwise, put the comma before.  This ensures that
	# signatures like the following render correctly (see issue  # 1001: https://github.com/sphinx-doc/sphinx/issues/1001):
	#
	#     foo([a, ]b, c[, d])
	#
	@start_td
	def visit_desc_parameter(self, node):
		if not self.tabling:
			return super().visit_desc_parameter(node)
		if self.first_param:
			self.first_param = 0
		elif not self.required_params_left:
			self.body.append(self.param_separator)
		if self.optional_param_level == 0:
			self.required_params_left -= 1
		if not node.hasattr('noemph'):
			self.body.append('<em>')

	@end_td
	def depart_desc_parameter(self, node):
		if not self.tabling:
			return super().depart_desc_parameter(node)
		if not node.hasattr('noemph'):
			self.body.append('</em>')
		if self.required_params_left:
			self.body.append(self.param_separator)

	def visit_desc_optional(self, node):
		if not self.tabling:
			return super().visit_desc_optional(node)
		self.optional_param_level += 1
		self.body.append('<span class="optional">[</span>')

	def depart_desc_optional(self, node):
		if not self.tabling:
			return super().depart_desc_optional(node)
		self.optional_param_level -= 1
		self.body.append('<span class="optional">]</span>')

	@start_td
	def visit_desc_annotation(self, node):
		if not self.tabling:
			return super().visit_desc_annotation(node)
		self.body.append('<em style="color:# AAA;margin-right:20px;">')

	@end_td
	def depart_desc_annotation(self, node):
		if not self.tabling:
			return super().depart_desc_annotation(node)
		self.body.append('</em>')

	@start_td
	def visit_desc_content(self, node):
		if not self.tabling:
			return super().visit_desc_content(node)

	@start_td
	def depart_desc_content(self, node):
		if not self.tabling:
			return super().depart_desc_content(node)
	# end special desc handling

	def visit_versionmodified(self, node):
		self.body.append(self.starttag(node, 'div', CLASS=node['type']))

	def depart_versionmodified(self, node):
		self.body.append('</div>\n')

	def visit_security(self, node):
		self.visit_admonition(node, 'security')

	def depart_security(self, node):
		self.depart_admonition(node)

	def visit_limit(self, node):
		self.visit_admonition(node, 'limit')

	def depart_limit(self, node):
		self.depart_admonition(node)

	def visit_stability(self, node):
		self.visit_admonition(node, 'stability')

	def depart_stability(self, node):
		self.depart_admonition(node)

	def visit_obsolete(self, node):
		self.visit_admonition(node, 'obsolete')

	def depart_obsolete(self, node):
		self.depart_admonition(node)

	def visit_misleading(self, node):
		self.visit_admonition(node, 'misleading')

	def depart_misleading(self, node):
		self.depart_admonition(node)


class TextWrapperDeux(TextWrapper):
	_wordsep_re = re.compile(
		r'((?<!`)[ \t\r\n\f\v]+(?!`)|'  # most whitespace; this used to be \s, but we want to avoid breaking on non-breaking spaces, so we can use them to preserve inline literals as non-breaking. TODO: there's a subtle problem with this regex in that there's an enforced space on the end and beginning of each string literal that can force an occasional odd wordwrap when a string literal falls at a line boundary.
		r'(?<=\s)(?::[a-z-]+:)`\S+|'              # interpreted text start
		r'[^\s\w]*\w+[a-zA-Z]-(?=\w+[a-zA-Z])|'   # hyphenated words
		r'(?<=[\w\!\"\'\&\.\,\?])-{2,}(?=\w))'  # em-dash
	)

	@property
	def wordsep_re(self):
		return self._wordsep_re

	def _wrap_chunks(self, chunks):
		"""_wrap_chunks(chunks : [string]) -> [string]
		The original _wrap_chunks uses len() to calculate width.
		This method respects wide/fullwidth characters for width adjustment.
		"""
		# drop_whitespace should be False, or a function object that can accept a string and drop undesirable whitespace, which defaults to str.strip
		drop_whitespace = getattr(self, 'drop_whitespace', True)
		lines = []
		if self.width <= 0:
			raise ValueError("invalid width %r (must be > 0)" % self.width)

		chunks.reverse()

		while chunks:
			cur_line = []
			cur_len = 0

			if lines:
				indent = self.subsequent_indent
			else:
				indent = self.initial_indent

			width = self.width - column_width(indent)

			if drop_whitespace and chunks[-1].strip() == '' and lines:
				del chunks[-1]

			while chunks:
				col_len = column_width(chunks[-1])

				if cur_len + col_len <= width:
					cur_line.append(chunks.pop())
					cur_len += col_len

				else:
					break

			if chunks and column_width(chunks[-1]) > width:
				self._handle_long_word(chunks, cur_line, cur_len, width)

			if drop_whitespace and cur_line and cur_line[-1].strip() == '':
				del cur_line[-1]

			if cur_line:
				lines.append(indent + str.lstrip(''.join(cur_line)))

		return lines


def lpc_wrap(obj, text, width=MAXWIDTH, **kwargs):  # pylint: disable=unused-argument
	wrap_obj = TextWrapperDeux(width=width, drop_whitespace=False, **kwargs)
	return wrap_obj.wrap(text)


# docutils uses two catch-all functions for raising errors on unimplemented visit/depart; pylint likes to complain, but we shouldn't implement them
class LPCTextTranslator(TextTranslator):  # pylint: disable=abstract-method
	# pylint: disable=unused-argument
	wrapper = lpc_wrap
	# TODO: perhaps instead of trying to use directive
	SECTIONS = {
		'applied': 'A',
		# note "concepts" (directory) here for plaintext, "concept" (direcive) in HTML translator
		'concepts': 'C',
		'driver': 'D',
		'efun': 'E',  # how to handle efun.de?
		'hook': 'H',
		'LPC': 'LPC',
		'master': 'M',
		'internals': 'I',
		# these probably don't work quite the same?
		# ideally obsolete/O works more like, I reference an efun which is defined with an :obsolete: option and so it gets flagged differently and given its own letter, or maybe even something better.
		# 'obsolete': 'O',
		# 'other': 'OTHER',
	}

	sig_groups = ["type", "addname", "name", "params", "returns", "annotation", "content"]
	backup_add_text = None

	def __init__(self, *a, **b):
		super().__init__(*a, **b)
		self.signatures = []
		self.hijack = [[]]
		# TODO: may use this at some date in the future, but the logic will be tricky to sort out, and we show hierarchy by nesting anyways...
		self.sectionchars = '==========='
		self.old_add_text = self.add_text

	# TODO: not sure if passing these is a great idea, but they add tons of useless markup to the field lists we use for arguments and history.
	def visit_literal_emphasis(self, node):
		pass

	def visit_literal_strong(self, node):
		pass

	def depart_literal_emphasis(self, node):
		pass

	def depart_literal_strong(self, node):
		pass

	def visit_field_name(self, node):
		self.new_state(0)

	def depart_field_name(self, node):
		self.add_text(': ')
		self.end_state(end=None)

	def visit_field_list(self, node):
		self.new_state(0)

	def depart_field_list(self, node):
		self.end_state()

	def depart_field_body(self, node):
		self.end_state(end=None)

	def visit_paragraph(self, node):
		if not isinstance(node.parent, (nodes.Admonition, addnodes.seealso, nodes.list_item)):
			self.new_state(0)

	def depart_paragraph(self, node):
		if not isinstance(node.parent, (nodes.Admonition, addnodes.seealso, nodes.list_item)):
			self.end_state()

	# TODO: semantic section should probably still increase sectionlevel in some way, but maybe introduce some sort of monitored adjustment to the title character? dunno, some weirdness here that I don't quite grok yet.
	def depart_title(self, node):
		"""Special handling to make the semantic_sibling_section idea work (i.e., sections that look like siblings in the document, but are actually child nodes)."""
		if isinstance(node.parent, nodes.section):
			char = self._title_char
		elif isinstance(node.parent, semantic_sibling_section):
			char = self.sectionchars[self.sectionlevel - 1]
		else:
			char = '^'
		text = ''.join(x[1] for x in self.states.pop() if x[0] == -1)
		self.stateindent.pop()  # just discard it

		if not node.parent or not len(self.states[-1]) or not len(self.states[-1][-1]) or not len(self.states[-1][-1][-1]) or not len(self.states[-1][-1][-1][-1]):
			self.states[-1].append(
				(-3, [text, '%s' % (char * column_width(text))]))
		else:
			self.states[-1].append(
				(-3, ['', text, '%s' % (char * column_width(text))]))

	def visit_semantic_sibling_section(self, node):
		self.new_state(0)

	def depart_semantic_sibling_section(self, node):
		self.end_state()

	# handle list_item differently for field_body and semantic_sibling_section.
	def visit_list_item(self, node):
		if 0 and isinstance(node.parent.parent, (nodes.field_body, semantic_sibling_section)):
			self.new_state(0)
		else:
			super().visit_list_item(node)

	def depart_list_item(self, node):
		if self.list_counter[-1] == -1:
			self.end_state(first='- ', end=None)
		elif self.list_counter[-1] == -2:
			pass
		else:
			self.end_state(first='%s. ' % self.list_counter[-1], end=None)

	def depart_bullet_list(self, node):
		# If we aren't part of some structure that needs preserving (for now just list_item), add a blank line after bullet lists; TODO: may need this elsewhere, or it may cause problems elsewhere.
		if not isinstance(node.parent, nodes.list_item):
			self.states[-1].append((0, ['']))
		return super().depart_bullet_list(node)

	# begin special handling for sig-related funcs
	def visit_desc(self, node):
		"""
		Hijack add_text until we depart_desc.

		The "reason" is that we want to do some horizontal alignment of synopsis parts.
		"""
		self.backup_add_text = self.add_text
		self.add_text = self.hijack_desc_text
		self.new_state(0)

	def depart_desc(self, node):
		"""
		Generate horizontally aligned text groups from the hijacked text, then clean up the state.

		High-alt view:
		- store a dict keyed by synopsis part, where each value contains a variable-length list
		- we zip_longest each of the individual array groups with the fillvalue as "", so we end up with all sigs having the same number of members w/in params (but each extra is a blank ""), and then we flatten this out into an array which we also zip_longest (this time with fillvalue " "), so that each string member gets expanded to the correct length.

		An example may be instructive:
		signature 1 = {
			addname: ["bob"],
			parameters: ["int arg", "string arg2"],
			content: ["x"]
		}

		signature 2 = {
			addname: ["thomas"],
			parameters: ["mapping x"],
			content: ["x"]
		}

		result:
		[
			("bob   ", "int arg  ", "string arg2", "x"),
			("thomas", "mapping x", "           ", "x"),
		]
		"""

		siglen = len(self.signatures)
		formatted_sigs = [[] for x in range(siglen)]

		# write a column of characters on each  formatted signature
		def distribute(column):
			for index, char in enumerate(column):
				formatted_sigs[index].append(char)

		# append the same characters across every sig
		# this is good for stable markup, like parentheses
		def extend(chars):
			for index in range(siglen):
				formatted_sigs[index].append(chars)

		bisected_groups = {}
		# each valid sig group
		for group in self.sig_groups:
			# zip_longest for each sig group to fill this group to the same number of members for all signatures, and then chain it so that we have a single iterable that will return the entire group.
			bisected_groups[group] = itertools.chain(itertools.zip_longest(*map(operator.itemgetter(group), self.signatures), fillvalue=""))

		# take a given group, walk through each member across all signatures, zip_longest to pad them all out to the size of the longest member, and then distribute a column of characters at a time.
		def pad(group):
			for line_part in bisected_groups[group]:
				for column in itertools.zip_longest(*line_part, fillvalue=" "):
					distribute(column)

		# pad each sig group in order; special treatment for params, to add the parenthetical
		for group in self.sig_groups:
			if group == "params":
				extend("(")
				pad(group)
				extend(")")
			else:
				pad(group)

		# push each formatted signature onto the states list
		for sig in formatted_sigs:
			self.states[-1].append((0, ["".join(sig)]))

		# reset
		self.add_text = self.backup_add_text
		self.end_state()
		self.signatures = []
		self.hijack = [[]]

	def hijack_desc_text(self, text):
		self.hijack[-1].append(text)

	def visit_desc_signature(self, node):
		if 'objtype' in node and node['objtype'] == "include":
			self.new_state(0)
			self.backup_add_text(node.astext())
		else:
			self.signatures.append({
				"type": [],
				"addname": [],
				"name": [],
				"params": [],
				"returns": [],
				"annotation": [],
				"content": [],
			})

	def depart_desc_signature(self, node):
		if 'objtype' in node and node['objtype'] == "include":
			return super().depart_desc_signature(node)
		else:
			pass

	def visit_desc_name(self, node):
		self.hijack.append(self.signatures[-1]["name"])

	def depart_desc_name(self, node):
		self.hijack.pop()

	def visit_desc_addname(self, node):
		self.hijack.append(self.signatures[-1]["addname"])

	def depart_desc_addname(self, node):
		self.hijack.pop()

	def visit_desc_type(self, node):
		self.hijack.append(self.signatures[-1]["type"])

	def depart_desc_type(self, node):
		self.hijack.pop()

	def visit_desc_returns(self, node):
		self.hijack.append(self.signatures[-1]["returns"])
		self.add_text(' -> ')

	def depart_desc_returns(self, node):
		self.hijack.pop()

	def visit_desc_parameterlist(self, node):
		pass

	def depart_desc_parameterlist(self, node):
		# trim the last comma/space off
		if len(self.signatures[-1]["params"]):
			self.signatures[-1]["params"][-1] = self.signatures[-1]["params"][-1][0:-2]

	def visit_desc_parameter(self, node):
		self.signatures[-1]["params"].append(node.astext() + ", ")
		raise nodes.SkipNode

	def visit_desc_optional(self, node):
		self.add_text('[')

	def depart_desc_optional(self, node):
		self.add_text(']')

	def visit_desc_annotation(self, node):
		self.hijack.append(self.signatures[-1]["annotation"])
		self.add_text(" //")

	def depart_desc_annotation(self, node):
		self.hijack.pop()

	def visit_desc_content(self, node):
		self.hijack.append(self.signatures[-1]["content"])
		self.add_text(self.nl)

	def depart_desc_content(self, node):
		self.hijack.pop()
	# end special handling for signature-related funcs

	# together, visit_ and depart_ provide special handling for our top-level sections
	_title_char = None

	def visit_section(self, node):
		if isinstance(node.parent, nodes.document):
			self.new_state(0)
			self._title_char = self.sectionchars[self.sectionlevel]
			self.sectionlevel += 1
		else:
			self.new_state()
			super().visit_section(node)

	def depart_section(self, node):
		if isinstance(node.parent, nodes.document):
			self.sectionlevel -= 1
		else:
			super().depart_section(node)
		self.end_state(end=None)

	def depart_reference(self, node):
		"""Intervene to add a letter representing the directory for most references."""
		# there are some special locations (like function synopses) where these additions make the documentation less useful.
		sect = None
		DEV_REF and debug(
			"DEV_REF: plaintext",
			{"node": node},
			{"refid": node.get("refid")},
			{"reftitle": node.get("reftitle")},
			{"refuri": node.get("refuri")},
			{"section": node.get("section")},
			{"line": node.line},
			{"source": node.source}
		)

		# not in function descriptions
		if not node.parent.tagname.startswith("desc"):
			todoc = node.get("todoc")
			if todoc:
				sect = self.SECTIONS.get(todoc.split("/")[0])

		if sect:
			self.add_text("(%s)" % sect)

	def visit_literal(self, node):
		"""Skip the ` around all literals except those inside a reference; begin capturing no-wrap text."""
		if not isinstance(node.parent, nodes.reference):
			self.add_text('`')
		self.set_pending_nowrap()

	def depart_literal(self, node):
		"""Skip the ` around all literals except those inside a reference; stop capturing no-wrap text."""
		self.satisfy_pending_nowrap()
		if not isinstance(node.parent, nodes.reference):
			self.add_text('`')

	def _visit_admonition(self, node):
		"""
		Make admonitions easier to spot.

		Set admonition body on line after title and indent by two cols.
		"""
		# this coincidentally fixed an issue where admonitions that didn't reach a second line in plaintext didn't have a blank line between them and the next line of text. If this is removed, we'll probably need to figure out what causes the missing blank line and fix it.
		self.new_state(2)
		self.states[-1].append((0, " "))

	def _make_depart_admonition(name):  # pylint: disable=no-self-argument
		def depart_admonition(self, node):  # pylint: disable=unused-argument
			self.end_state(first="<!> " + admonitionlabels[name] + ': ')
		return depart_admonition

	# TODO: add translations.
	# add all admonitions (overload behavior for existing admonitions we plan to use)
	# 	ours
	visit_security = _visit_admonition
	visit_limit = _visit_admonition
	visit_stability = _visit_admonition
	visit_obsolete = _visit_admonition
	visit_misleading = _visit_admonition
	# 	not ours
	visit_warning = _visit_admonition
	visit_note = _visit_admonition
	visit_tip = _visit_admonition

	# add all admonitions
	# 	ours
	depart_security = TextTranslator._make_depart_admonition("security")
	depart_limit = TextTranslator._make_depart_admonition("limit")
	depart_stability = TextTranslator._make_depart_admonition("stability")
	depart_obsolete = TextTranslator._make_depart_admonition("obsolete")
	depart_misleading = TextTranslator._make_depart_admonition("misleading")
	# 	not ours
	depart_warning = _make_depart_admonition("warning")
	depart_note = _make_depart_admonition("note")
	depart_tip = _make_depart_admonition("tip")

	def nowrap_add_text(self, text):
		"""Replace all spaces with non-breaking spaces."""
		return self.old_add_text(text.replace(" ", chr(160)))

	def set_pending_nowrap(self):
		"""
		Replace add_text with nowrap_add_text.

		Enables us to give special treatment to text added by all child nodes within a literal.
		"""
		self.add_text = self.nowrap_add_text

	def satisfy_pending_nowrap(self):
		"""Reinstate the original add_text function."""
		self.add_text = self.old_add_text

	def end_state(self, **kw):
		"""
		Finalize the state begun in a previous new_state call.

		We're here because we needed to make some low-level tweaks to how Sphinx indents/wraps.

		Most of the original sphinx end_state logic is now in end_state_original so that we can develop against it; there's some reasonable chance there are subtle unintentional bugs in my rewrite (not to mention the original :). The logic Sphinx used to format here was difficult to reason about, on top of the underlying data structure also being hard to reason about.

		I took an initial swing at rewriting this but ran into some complications with its model and took another try. I added it into the comparison here to make sure I was addressing is shortcomings but keeping its refinements over original.

		These should probably remain in place for learning/research/debug purposes for the forseeable future.
		"""
		content = self.states.pop()
		maxindent = sum(self.stateindent)
		indent = self.stateindent.pop()

		if DEV_PLAINTEXT > 0:
			orig = self.end_state_original(copy.deepcopy(content), maxindent, indent, **kw)
			previous = self.end_state_rewrite_1(copy.deepcopy(content), maxindent, indent, **kw)
			present = self.end_state_rewrite_2(content, maxindent, indent, **kw)
			orig != present and interrogate(
				# pylint: disable=protected-access
				"DEV_PLAINTEXT",
				"mismatch between output from old/new end_state()",
				{"caller": sys._getframe().f_back.f_code.co_name},
				{"content": content},
				{"maxindent": maxindent},
				{"indent": indent},
				{"ORIGINAL_END_STATE": orig},
				DEV_PLAINTEXT > 2 and {"PREVIOUS_END_STATE": previous},
				{"PRESENT_END_STATE": present},
			)
			self.states[-1].extend(present)
		else:
			self.states[-1].extend(
				self.end_state_rewrite_2(content, maxindent, indent, **kw)
			)

	def end_state_original(self, content, maxindent, indent, wrap=True, end=[''], first=None):  # pylint: disable=dangerous-default-value
		"""
		Take a state popped off the stack, wrap/format/indent it, append any first/end, and return it.

		Note that this is mostly identical to the original end_state code in Sphinx's plaintext writer (https://github.com/sphinx-doc/sphinx/blob/master/sphinx/writers/text.py) except that I have made some small modifications to support calling multiple copies of end_state and comparing the results. I have also added debug messages, and quite a few comments on the difficult-to-understand logic. The summary below includes before/after sections to cover logic that has been factored out of this function but is part of the original formatting process.

		The high-altitude view:
		- Before this is called, we pop a set of content/indent off of their respective stacks, and compute a maxindent based on how far we're already indented.
		- Then, declare a local function do_format, and iterate over the itemindent/item pairs in content, collecting items with a special (-1) indent in 'toformat' until we run into an item without the special indent, or exit the loop.
		- Once this formatting pass is complete, if there is a 'first', jump through some hoops to shift it onto the result without having to rewrap/format everything.
		- After this process, result is appended to the final item in the next-highest "state" (i.e., self.states[-1].extend(result)).
		"""
		result = []
		toformat = []

		def do_format():
			if not len(toformat):
				return
			DEV_PLAINTEXT > 3 and debug(
				"DEV_PLAINTEXT",
				"end_state_original: formatting",
				{"toformat": toformat},
				{"content": content}
			)
			if wrap:
				res = self.wrapper(''.join(toformat), width=MAXWIDTH - maxindent)
			else:
				res = ''.join(toformat).splitlines()
			if end:
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_original: appending end to res",
					{"end": end},
					{"res": res}
				)
				res += end
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_original: new res",
					{"res": res}
				)
			result.append((indent, res))
		for itemindent, item in content:
			# this if block added JUST for debug
			if end:
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_original: looping content(start)",
					{"itemindent": itemindent},
					{"item": item},
					"before formatting:",
					{"result": result}
				)

			if itemindent == -1:
				# the rst parser uses -1 as a special indent value that indicates the node should be combined with peers, wrapped, and be appended to its parent with a regular indent value.
				toformat.append(item)
			else:
				# format anything appended to to_format on a previous iteration in case something is pending
				do_format()
				# but append this round's items without passing through formatter (ostensibly they have already been wrapped at some deeper level of the tree)
				result.append((indent + itemindent, item))
				toformat = []

			# this if block added JUST for debug
			if end:
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_original: looping content(end)",
					"after formatting:",
					{"result": result}
				)
		do_format()
		if first is not None and result:
			DEV_PLAINTEXT > 3 and debug(
				"DEV_PLAINTEXT",
				"end_state_original: before prepending 'first'",
				{"result": result}
			)
			# We have a 'first' to prepend, but it'll probably mess up our wrapping, so we pop the first item off of the result, save the rest of our original result parse, and reset the 'result' variable to empty (because we're about to re-use it)
			itemindent, item = result[0]
			result_rest, result = result[1:], []
			if item:
				# Then we take 'first', prepend it to the first item, and pass these alone through the formatter.
				toformat = [first + ' '.join(item)]
				do_format()  # re-create `result` from `toformat`
				# get the first item in the newly-wrapped result
				_, new_item = result[0]
				# insert only the first line of it at the beginning of the result array.
				result.insert(0, (itemindent - indent, [new_item[0]]))
				# add any additional lines
				result[1] = (itemindent, new_item[1:])
				# tack on all of the rest of the original wrapped output
				result.extend(result_rest)

		DEV_PLAINTEXT > 3 and debug(
			"DEV_PLAINTEXT",
			{"end_state_original: final result": result}
		)
		return result

	def prep(self, wrap, items, maxindent):
		"""return wrapped/unwrapped list of lines in <items>."""
		if wrap:
			wrapped = self.wrapper("".join(items), width=MAXWIDTH - maxindent)
			DEV_PLAINTEXT > 4 and debug(
				"DEV_PLAINTEXT",
				"prep: wrapping",
				{"width": MAXWIDTH - maxindent},
				{"items list": items},
				{"joined items": "".join(items)},
				{"result": wrapped}
			)
			return wrapped
		else:
			DEV_PLAINTEXT > 4 and debug(
				"DEV_PLAINTEXT",
				"prep: not wrapping (simple join/splitlines)",
				{"items": items},
				{"maxindent": maxindent}
			)
			return "".join(items).splitlines()

		# TODO: thoroughly document this tortured logic... :)
		# TODO: more than one line in here is assuming item/temp will be a list, but in some cases it can be a string; there may be subtle bugs lurking
	def end_state_rewrite_2(self, content, maxindent, indent, wrap=True, end=[''], first=None):  # pylint: disable=dangerous-default-value
		"""
		Take a state popped off the stack, wrap/format/indent it, append any first/end, and return it.

		Note: this function takes an argument 'indent', describing the indent for the state we are terminating. Each "state" tuple's member also includes an item which is a local indentation for that member; loops in this function unpack this local indentation as 'dent'.

		High-altitude view:
		In contrast to original, we use two loops:
			loop 1: use enumerate to loop over index/indent/item in content so we can append 'first' as we go; for this round, the goal is building out the structure of 'result' without performing any wrapping
			loop 2:
		"""
		result = []
		processed = []

		DEV_PLAINTEXT > 3 and debug(
			"DEV_PLAINTEXT",
			"end_state_rewrite_2",
			{"content": content},
			{"wrap": wrap}
		)
		for index, (dent, item) in enumerate(content):

			if index == 0 and first:
				# first item in content AND we have a value for 'first'
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_rewrite_2",
					"adding 'first' to 'item'",
					{"first": repr(first)},
					{"item": repr(item)}
				)
				# item might be a string or a list
				if isinstance(item, str):
					if dent == -1:
						item = first + item
					else:
						item = [first + item]
				else:
					item[0] = first + " ".join(item)

				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_rewrite_2",
					"added 'first' to 'item'",
					{"item": repr(item)}
				)

			# -1 indents are supposed to be collected into a list and passed through the formatter together; the problem is that we don't know if we're done collecting them until after the present round.
			# So, we use references to make accumulating these a little easier. The first time we encounter a -1, append our (empty) processed list directly into 'result'. Each subsequent time we encounter a -1 (until we encounter a normal indent value) we can just use processed.append(item) to include it in the appropriate location within 'result'.
			if dent == -1:
				if not len(processed):
					# append ref to 'processed' on first pass
					result.append((dent, processed))
					DEV_PLAINTEXT > 3 and debug(
						"DEV_PLAINTEXT",
						"end_state_rewrite_2",
						"appending new 'processed' to result",
						{"appending": (dent, processed)},
						{"result": result}
					)
				# then use reference to append each item into place within 'result'
				processed.append(item)
				DEV_PLAINTEXT > 3 and interrogate(
					"DEV_PLAINTEXT",
					"end_state_rewrite_2",
					"appended 'item' to processed",
					{"item": item},
					{"processed": processed},
					DEV_PLAINTEXT > 5 and {"result": result}
				)
			else:
				# not a special indent, so immediately append to result, and reset processed in case pending iterations need it
				processed = item
				result.append((indent + dent, processed))
				processed = []

		DEV_PLAINTEXT > 3 and debug(
			"DEV_PLAINTEXT",
			"end_state_rewrite_2",
			{"intermediate result (after structure pass)": result}
		)

		final_result = []

		# now we're ready to loop through result to perform the formatting pass
		for index, (dent, item) in enumerate(result):
			DEV_PLAINTEXT > 3 and debug(
				"DEV_PLAINTEXT",
				"end_state_rewrite_2",
				"format pass: starting state",
				{"index": index},
				{"dent": dent},
				{"item": item},
				"relevant function parameters:",
				{"first": first, "end": end, "indent": indent},
			)
			start = rest = temp = None

			DEV_PLAINTEXT > 3 and debug(
				"DEV_PLAINTEXT",
				"end_state_rewrite_2",
				"format pass:",
				"indentations: %d - %d = %d" % (dent, indent, dent - indent)
			)

			if dent == -1:
				# -1 indents shouldn't survive this round; they're supposed to land in the formatter.
				dent = indent
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_rewrite_2",
					"format pass: handling -1 dent",
					"changing -1 dent to function indent(%d)" % indent,
				)

				temp = self.prep(wrap, item, maxindent + dent)  # see prep for debug/print
			else:
				# otherwise, use item unchanged
				temp = item

			# TODO: evaluate whether the trees below are necessary given that only -1 should get formatted
			# TODO: follow the -1 format rule in all remaining trees below
			# Ideally I can separate these into two steps (wrap or not, handle first/end/not)

			# three cases; first, end, and everyone else
			if index == 0 and first:
				if len(temp):
					# First was earlier prepended to this item, so we need some special handling: 'first' gets appended at the parent's indentation level, and then afterwards we use our local indent.
					# the following 2 lines are the only time we call prep with anything but maxindent+dent (but keep in mind that "dent" is no longer a "safe" value; use indent)
					start = (0, self.prep(wrap, temp[0], maxindent))
					rest = (dent, self.prep(wrap, temp[1:], maxindent))
					DEV_PLAINTEXT > 3 and debug(
						"DEV_PLAINTEXT",
						"end_state_rewrite_2",
						"format pass: 'first':",
						{"temp": temp},
						{"start": start},
						{"rest": rest}
					)

			elif end and index + 1 == len(result):
				if end == temp[-1:]:
					pass
					# this feels like a kludge, but it might still be the best response. Basically this catches the default end=[''] and keeps it from being reappended when it's already present from a lower level.
					# I think they get eaten in the original formatter when it uses "".join(items).splitlines()
					#
					# Leaving debug messages in place in case there's a compelling reason to get this "right" in the near term (this might be related to some other output inconsistency)
					#
					# debug("TODO:"
					# 	"end_state_rewrite_2",
					# 	"in some poorly understood circumstances, 'end' was getting appended more than once; we presently only append 'end' if the last item in 'temp' isn't identical to it. This feels like a big kludge, so debugging everything I can think of when this occurrs to see if there's a better path.",
					# 	{"caller": sys._getframe(1).f_back.f_code.co_name},
					# 	{"temp": temp},
					# 	{"item": item},
					# 	{"item+end": item+end},
					# 	{"dent": dent},
					# 	"function args",
					# 	{"content": content, "maxindent": maxindent, "indent": indent, "wrap": wrap, "end": end, "first": first},
					# 	{"target state": self.states[-1]}
					# )

				else:
					# debug("TODO:"
					# 	"end_state_rewrite_2",
					# 	"Need the alt state.",
					# 	{"caller": sys._getframe(1).f_back.f_code.co_name},
					# 	{"temp": temp},
					# 	{"end": end}
					# )
					temp = temp + end

				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_rewrite_2",
					"format pass: last round",
					"setting 'rest' to 'temp'; contrast with 'item+end' (whenever dent != -1, both of these versions should be identical)",
					{"temp": temp},
					{"item+end": item + end},
					{"dent": dent}
				)

				rest = (dent, temp)

			else:
				DEV_PLAINTEXT > 3 and debug(
					"DEV_PLAINTEXT",
					"end_state_rewrite_2",
					"format pass: every other round",
					"setting 'rest' to 'temp'; contrast with 'item'",
					{"temp": temp},
					{"item": item},
					{"dent": dent}
				)
				rest = (dent, temp)

			if start:
				final_result.append(start)
			if rest:
				final_result.append(rest)

		DEV_PLAINTEXT > 3 and debug(
			"DEV_PLAINTEXT",
			"end_state_rewrite_2",
			{"final_result": final_result}
		)
		return final_result

	# no special debug or doc for now; will cross this bridge if a problem with the new function that really requires comparing these actually comes up
	# hoping to actually cull this before too long if nothing does
	def end_state_rewrite_1(self, content, maxindent, indent, wrap=True, end=[''], first=None):  # pylint: disable=dangerous-default-value
		result = []
		queue = []
		processed = []

		for index, (dent, item) in enumerate(content):

			if index == 0 and first:
				if isinstance(item, str):
					item = first + item
				else:
					item[0] = first + " ".join(item)

			if dent == -1:
				if not len(processed):
					result.append((indent, processed))
					queue.append(processed)
				processed.append(item)
			else:
				# flush?
				processed = item
				result.append((indent + dent, processed))
				processed = []

		final_result = []

		for index, (dent, item) in enumerate(result):

			start = rest = None

			if first and index == 0:
				temp = self.prep(wrap, item, maxindent + dent)
				if len(temp):
					start = (dent - indent, self.prep(wrap, temp[0], maxindent))
					rest = (dent, self.prep(wrap, temp[1:], maxindent))

			elif end and index + 1 == len(result):
				if dent not in (0, -1):
					rest = (dent, self.prep(wrap, item, maxindent + dent) + end)
				else:
					prepped = self.prep(wrap, item, maxindent + dent)
					rest = (dent, prepped + end)

			else:
				if item not in queue:
					rest = (dent, item)
				else:
					rest = (dent, self.prep(wrap, item, maxindent + dent))
			if start:
				final_result.append(start)
			if rest:
				final_result.append(rest)

		return final_result

	def report_calls(self, name):
		debug(
			"DEV_PLAINTEXT",
			"called LPCTextTranslator.%s" % name
		)
		returned = object.__getattribute__(self, name)
		return returned


# TODO: another distinct possibility is that I need to add a "transform" or modify the doctree at doctree-resolved to massage the document state into something that is straightforward to doxify...
# AGH.
# not sure whether I should start from scratch or from text
# class LPCDoxygenTranslator(nodes.NodeVisitor):
# TODO: Either need to document includes with one of the below, or by schleping them up to the top of the document somehow before writing
# \class MyClassName include.h path/include.h
# \class MyClassName myhdr.h "path/myhdr.h"
# \headerfile <header-file> [<header-name>]
class LPCDoxygenTranslator(LPCTextTranslator):
	_prefix = ""
	_prefix_len = 0

	def __init__(self, *a, **b):
		super().__init__(*a, **b)
		# a[0] is document, a[1] is the builder
		# we want to set a[1].out_suffix to either md or c at whatever the best time is.
		# debug("VALHALLA", self.builder.env.found_docs)

	def end_state(self, **kw):
		"""Override end_state to *not* wrap."""
		content = self.states.pop()
		maxindent = sum(self.stateindent)
		indent = self.stateindent.pop()

		kw["wrap"] = False

		self.states[-1].extend(self.end_state_rewrite_2(content, maxindent, indent, **kw))
		# print("STATS", self.states[-1])

	@staticmethod
	def build_signature(sig):
		signature = []
		params = False
		for part in sig.traverse():
			if isinstance(part, addnodes.desc_type):
				signature.append("%s" % part.astext())
			elif isinstance(part, addnodes.desc_name):
				signature.append(part.astext())
			elif isinstance(part, addnodes.desc_parameterlist):
				params = True
				signature.append("(%s)" % ", ".join(map(lambda x: x.astext(), part.traverse(addnodes.desc_parameter))))

		if not params:
			signature.append("()")

		return "".join(signature)

	def build_args(self, node):
		return self._consume_node(node)

	def build_topical_doc(self, node):
		self._set_prefix("", 3)

		# build doc parts
		# make this an ordered dict, pre-build the part in order
		parts = OrderedDict()
		parts["definition"] = None
		parts["description"] = None
		parts["synopsis"] = None
		parts["usage"] = None
		parts["history"] = None
		parts["seealso"] = None
		parts["arguments"] = None

		for section in node.traverse(nodes.section):
			if "DESCRIPTION" in section["ids"]:
				parts["description"] = section
			elif len(set(["SYNOPSIS", "TYPE", "LANG", "CONCEPT", "DIRECTORY", "COMMAND", "DRIVER", "META", "GUIDE", "TOPIC"]).intersection(set(section["ids"]))):
				parts["synopsis"], parts["definition"] = self.build_topic_synopsis(section)
				section.parent.remove(section)
			elif "USAGE" in section["ids"]:
				parts["usage"] = self.build_usage(section)
				section.parent.remove(section)

		for section in node.traverse(semantic_sibling_section):
			if section.tagname == "history":
				parts["history"] = self.build_history(section)
				section.parent.remove(section)
			elif section.tagname == "seealso":
				parts["seealso"] = self.build_seealso(section)
				section.parent.remove(section)

		for fieldlist in node.traverse(nodes.field_list):
			if "id" in fieldlist and fieldlist["id"] == "arguments":
				if not parts["arguments"]:
					parts["arguments"] = []
				parts["arguments"].extend(self.build_args(fieldlist))

		# in doxygen output our synopsis is much lower in the document:
		# description
		# synopsis * with 0 args, parenthesis is left off; check html/plain outputs for same
		# usage
		# history
		# seealso *

		# late parse of description after children are pulled out
		parts["description"] = self.build_description(parts["description"])

		doc = [(0, part) for section, part in parts.items() if part]

		self.states[-1].extend(doc)

	def build_function_doc(self, node):
		self._set_prefix(" * ", 3)

		# build doc parts
		# make this an ordered dict, pre-build the part in order
		parts = OrderedDict()
		parts["description"] = None
		parts["synopsis"] = None
		parts["usage"] = None
		parts["history"] = None
		parts["seealso"] = None
		parts["definition"] = None
		parts["arguments"] = None

		for section in node.traverse(nodes.section):
			if "DESCRIPTION" in section["ids"]:
				parts["description"] = section
			elif "SYNOPSIS" in section["ids"]:
				parts["synopsis"], parts["definition"] = self.build_function_synopsis(section)
				section.parent.remove(section)
			elif "USAGE" in section["ids"]:
				parts["usage"] = self.build_usage(section)
				section.parent.remove(section)

		for section in node.traverse(semantic_sibling_section):
			if section.tagname == "history":
				parts["history"] = self.build_history(section)
				section.parent.remove(section)
			elif section.tagname == "seealso":
				parts["seealso"] = self.build_seealso(section)
				section.parent.remove(section)

		for fieldlist in node.traverse(nodes.field_list):
			if "id" in fieldlist and fieldlist["id"] == "arguments":
				if not parts["arguments"]:
					parts["arguments"] = []
				parts["arguments"].extend(self.build_args(fieldlist))

		# in doxygen output our synopsis is much lower in the document:
		# description
		# synopsis * with 0 args, parenthesis is left off; check html/plain outputs for same
		# usage
		# history
		# seealso *

		# late parse of description after children are pulled out
		parts["description"] = self.build_description(parts["description"])

		doc = [(0, ["public class %s {" % node['objtype']]), (3, ["/**"])]
		[doc.append((3, part)) for section, part in parts.items() if part]
		doc.append((0, ["}"]))

		self.states[-1].extend(doc)

	def _set_prefix(self, prefix, offset):
		self._prefix = prefix
		self._offset = offset

	def _consume_node(self, node):
		self.new_state(0)
		node.walkabout(self)
		node.parent.remove(node)
		return [
			self._prefix + (" " * (indent - self._offset)) + line
			for indent, lines in self.states.pop() if len(lines)
			for line in lines
		]

	def build_description(self, node):
		return self._consume_node(node)

	def build_usage(self, node):
		usage = ["@usage{"]
		# usage.extend([x.astext().splitlines() for x in node[1:-1]])
		for child in node[1:]:
			usage.extend(child.astext().splitlines())
		usage.extend(["}", ""])
		return [self._prefix + x for x in usage]

	def build_history(self, node):
		history = ["@history{"]
		history.extend([x.astext() for x in node.traverse(nodes.list_item)])
		history.extend(["}", ""])
		return [self._prefix + x for x in history]

	def build_ref(self, node):
		section = node.get("section")
		if section in ["efun", "applied", "master"]:
			return "{0}::{1}()".format(section, node.get("reftitle"))
		else:
			# debug("I don't know", node)
			todoc = node.get("todoc", node.get("refuri"))
			if todoc:
				desc = node.astext()
				if "::" in desc:  # may be cheating...
					return desc

				docpath = todoc.split("/")
				return '@ref driver_{0} "{1}"'.format("_".join(docpath), desc) if node.get("todoc") else '@subpage driver_{0} "{1}"'.format("_".join(docpath), desc)
			else:

				#
				# I think there may be two different uses reaching here:
				# A = TOC docs?
				return "@ref {0}".format(node.astext())
				# B = efun? <reference anchorname="" internal="True" refuri="">add_verb</reference>
				docpath = self.builder.current_docname.split("/")
				docpath.pop()
				return "@ref {1}.*".format("/".join(docpath), node.astext())

				# \class <name> [<header-file>] [<header-name>]
				# I could also add all of the individual elements to a group and just document the group elsewhere...

	def build_seealso(self, node):
		# TODO: a reference like :doc:'structs' will break here because it's a native role and the node looks like: <reference internal="True" refuri=""><inline classes="doc">struct</inline></reference>; (not mutually exclusive) options seem to be:
		# - just kill them silently
		# - throw an error
		# - fallback to another parsing routine to divine section
		refs = [self.build_ref(x) for x in node.traverse(nodes.reference)]
		return [self._prefix + "@see " + ", ".join(refs)]

	def build_synopsis(self, node):
		# traverse our nodes, build a desc in synopsis, append directly to state
		synopsis = ["@synopsis{"]
		signatures = []

		for sig in node.traverse(addnodes.desc_signature):
			if "objtype" in sig and sig["objtype"] == "include":
				synopsis = ["@headerfile " + sig.astext().split()[-1], ""] + synopsis
			else:
				signatures.append(self.build_signature(sig))
		if not len(signatures):
			return None
		synopsis.extend(signatures)
		synopsis.extend(["}", ""])
		return synopsis

	def build_topic_synopsis(self, node):
		synopsis = self.build_synopsis(node)
		docpath = self.builder.current_docname.split("/")
		title = "{0} {{#driver_{1}}}".format(docpath[-1], "_".join(docpath))
		self.builder.out_suffix = ".md"
		return [self._prefix + x for x in synopsis] if synopsis else None, [title, "=" * len(title)]

	def build_function_synopsis(self, node):
		synopsis = self.build_synopsis(node)
		self.builder.out_suffix = ".c"
		# return [" * " + x for x in synopsis], ["*/"] + [sig + ";" for sig in signatures]
		return [self._prefix + x for x in synopsis], ["**/"] + [synopsis[-3] + ";"]

		# temp reference
		# 		'topic': LPCTopic,
		# 	'concept': LPCTopic,
		# 	'driver': LPCTopic,
		# 	'directory': LPCTopic,
		# 'lang': LPCLang,
		# 	'syntax': LPCSyntax,
		# 		'keyword': LPCSyntax,
		# 			'modifier': LPCVar,
		# 			'type': LPCType,
		# 		'operator': LPCSyntax,
		# 	'pragma': LPCVar,
		# 'function': LPCFunction,
		# 	'applied': LPCApplied,
		# 	'efun': LPCFunction,
		# 	'hook': LPCHook,
		# 	'master': LPCFunction,
		# 	# 'obsolete': LPCFunction,
		# 'guide': LPCGuide,
		# 	# 'internal': LPCGuide,
		# 	# 'tutorial': LPCGuide,?
		# 'command': LPCCommand,

	def visit_section(self, node):
		if node.tagname in ["function", "applied", "efun", "master"]:
			# skip the node and dive off into our own processing routine
			self.build_function_doc(node)
			raise nodes.SkipNode
		elif node.tagname in ["hook", "topic", "command", "directory", "lang", "type", "syntax", "keyword", "modifier", "operator", "meta", "guide"]:
			self.build_topical_doc(node)
			raise nodes.SkipNode
		else:
			self.new_state(0)
			self.sectionlevel += 1

	def depart_section(self, node):
		# all other types use skipnode, so they won't get here
		self.sectionlevel -= 1
		self.end_state()

	def visit_title(self, node):
		DEV_DOXYGEN and debug(
			"DEV_DOXYGEN: skipping title",
			node,
			node.parent,
			node.parent.tagname
		)
		# TODO: we can skip meta titles like SYNOPSIS or HISTORY, but sub-section titles will eventually need to be let back through
		# raise nodes.SkipNode
		if node.parent.tagname != "subtopic":
			raise nodes.SkipNode
		else:
			self.new_state(0)
			self.add_text("{0} ".format("#" * self.sectionlevel))

	def depart_title(self, node):
		self.add_text(" #")
		self.end_state()

	def visit_literal(self, node):
		# depending on classes, append a command to flag the next word?
		if "any" in node["classes"]:
			self.add_text("@a")
		else:
			self.add_text("`")

	def depart_literal(self, node):
		self.add_text("`")

	def visit_emphasis(self, node):
		self.add_text("<em>")

	def depart_emphasis(self, node):
		self.add_text("</em>")

	def visit_strong(self, node):
		self.add_text("<b>")

	def depart_strong(self, node):
		self.add_text("</b>")

	def visit_bug(self, node):
		self.add_text("@bug ")

	def depart_bug(self, node):
		self.add_text("\n")

	def _make_visit_admonition(name):  # pylint: disable=no-self-argument
		def visit_admonition(self, node):  # pylint: disable=unused-argument
			self.new_state(0)
			self.add_text("@par %s:" % name)
		return visit_admonition

	def _depart_admonition(self, node):
		self.end_state()

	visit_security = _make_visit_admonition("security")
	visit_limit = _make_visit_admonition("limit")
	visit_stability = _make_visit_admonition("stability")
	visit_obsolete = _make_visit_admonition("obsolete")
	visit_misleading = _make_visit_admonition("misleading")
	# 	not ours
	visit_warning = _make_visit_admonition("warning")
	visit_note = _make_visit_admonition("note")
	visit_tip = _make_visit_admonition("tip")

	# add all admonitions
	# 	ours
	depart_security = _depart_admonition
	depart_limit = _depart_admonition
	depart_stability = _depart_admonition
	depart_obsolete = _depart_admonition
	depart_misleading = _depart_admonition
	# 	not ours
	depart_warning = _depart_admonition
	depart_note = _depart_admonition
	depart_tip = _depart_admonition

	# def visit_note(self, node):
	# 	self.add_text("@note ")

	# def depart_note(self, node):
	# 	self.add_text("\n")

	# def visit_warning(self, node):
	# 	self.add_text("@warning ")

	# def depart_warning(self, node):
	# 	self.add_text("\n")
	#
	# def visit_field_name(self, node):
	# 	pass

	# def depart_field_name(self, node):
	# 	pass

	# def visit_list_item(self, node):
	# 	self.hijack.append([])
	#
	def visit_literal_block(self, node):
		self.add_text("~~~{.c}")
		self.new_state(0)

	def depart_literal_block(self, node):
		self.end_state()
		self.add_text("~~~")

	def visit_todo_node(self, node):
		raise nodes.SkipNode

	def visit_reference(self, node):
		self.add_text(self.build_ref(node))
		raise nodes.SkipNode


def char_role(name, rawtext, text, lineno, inliner, options={}, content=[]):  # pylint: disable=unused-argument,too-many-arguments,dangerous-default-value
	"""Describe a character given by unicode name.

	Returns 2 part tuple containing list of nodes to insert into the
	document and a list of system messages.  Both are allowed to be
	empty.

	:param name: The role name used in the document.
	:param rawtext: The entire markup snippet, with role.
	:param text: The text marked with the role.
	:param lineno: The line number where rawtext appears in the input.
	:param inliner: The inliner instance that called us.
	:param options: Directive options for customization.
	:param content: The directive content for customization.
	"""
	try:
		character = nodes.unicodedata.lookup(text)
	except KeyError:
		msg = inliner.reporter.error(
			':char: argument %s must be valid unicode name at line %d' % (text, lineno))
		prb = inliner.problematic(rawtext, rawtext, msg)
		return [prb], [msg]
	# app = inliner.document.settings.env.app  # TODO: remove?
	describe_char = "(U+%05X %s)" % (ord(character), text)
	char = nodes.inline("char:", "char:", nodes.literal(character, character))
	char += nodes.inline(describe_char, describe_char)
	return [char], []


# not sure whether I should start from scratch or from text
class LPCDoxygenBuilder(TextBuilder):
	translator_class = LPCDoxygenTranslator
	name = 'doxygen'
	format = 'doxygen'
	out_suffix = '.c'

	# todo: document what this fixed...
	def get_relative_uri(self, fromdocname, todocname, typ=None):
		return todocname
		# return super().get_relative_uri("", todocname, typ)

	def get_target_uri(self, docname, typ=None):
		debug("getting target URI", docname, typ)
		return docname


# TODO: evaluate whether it is reasonable to customize the builder to throw out new micro-docs for given topics? There are a few possible avenues; using nodes on the writer/builder/translator to throw new docs into the write queue, setting the writer/builder to traverse each doctree and imperatively write out some distinct docs (probably a lot more wasteful?, but perhaps more obvious?) Could also possibly configure the *directives* to trigger this (throw a new doc in the queue with a reference to that specific node?)
class LPCTextBuilder(TextBuilder):
	"""Custom 'plain' builder to generate files with no extension."""
	# need a different name to avoid clash with builtin "text" builder
	name = 'plain'
	format = 'text'
	out_suffix = ''  # no file extension


class Validator(object):
	"""
	Basic validator functionality.
	"""
	app = name = doc = codes = lineno = infraction_type = None
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

		return lineno if lineno is not None else 0

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
						print(doc_infraction_template.format(line or "?", infraction.code, infraction.message))
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

			if app.statuscode:
				# if we have a statuscode, the exit code we throw will stop the makefile from printing the output directory; simplest fix is printing it here
				print("Build finished. The '{:}' files are in {:}/".format(app.builder.name, app.outdir))


class ValidateSource(Validator):
	"""
	Enforces generic codestyle rules.

	Rules of this kind should be testable with simple heuristics and 0 semantic knowledge.

	1: Nothing but directives and comments at the document level; this means a line should be blank, should begin with two periods and a space, or should have some quantity of blank spaces (probably coming in pairs)
	2: Only valid directives are used at the top level of a document:
		concept, efun, master, hook...

	TODO: blank lines aren't *always* ok; should we try to specify when they are and aren't?
	"""
	INDENT_STEP = 2
	stack = None
	codes = {
		# pylint: disable=unnecessary-lambda
		# disabled the line-too-long rule, but saving for posterity
		# "line-too-long": lambda n: "len: {:} (max: {:})".format(n, ValidateSource.MAX_SOURCE_LINE_LEN),
		"under-indent": lambda n, expected: "found {:>2} spaces, expected {:>2}".format(n, expected),
		"over-indent": lambda n, expected: "found {:>2} spaces, expected {:>2}".format(n, expected),
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

		if cls.handle_directive(line, 0):
			return True

		if cls.handle_field(line, 0):
			return True

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

				cls._fail("over-indent", cls.lineno, n=indented, expected=pad)  # over-indent
				return True
			elif not indented % cls.INDENT_STEP:
				# indent is divisible by our step
				return False
			else:
				cls._fail(
					"under-indent",
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

	# TODO: perhaps amusingly, this function was massively indented; refactored into indent and _generate_indent_linter above; keeping code until I'm more confident it works.
	# @classmethod
	# def indent2(cls, depth):
	# 	"""
	# 	Return an indent linter which accounts for the indent.

	# 	TODO: don't be lazy, what do these return values mean?
	# 	"""
	# 	pad = depth * cls.INDENT_STEP
	# 	indent = " " * (pad)

	# 	def lint_indent(line):
	# 		"""Lint indent lines."""
	# 		if not len(line):  # and initial_blank:  # TODO: yuck
	# 			return True  # OK

	# 		indented = len(line) - len(line.lstrip())

	# 		if line.startswith(indent):
	# 			# OK
	# 			if line[pad] == " ":
	# 				# unless this is some valid markup structure, like a list or possibly a table.
	# 				if cls.handle_markup(line, pad):
	# 					return True

	# 				cls._fail("over-indent", cls.lineno, n=indented, expected=pad)  # over-indent
	# 				return True
	# 			elif cls.handle_directive(line, pad):
	# 				return True  # OK
	# 			elif cls.handle_field(line, pad):
	# 				return True

	# 		else:
	# 			if line.startswith(indent[0:-cls.INDENT_STEP]) and line[pad - cls.INDENT_STEP] != " ":
	# 				# single-block dedent?
	# 				return False  # POP
	# 			else:
	# 				if not indented % cls.INDENT_STEP:
	# 					# this might be a proper multi-block dedent
	# 					return False

	# 				cls._fail(
	# 					"under-indent",
	# 					cls.lineno,
	# 					n=indented,
	# 					expected=pad
	# 				)
	# 				return True

	# 	return lint_indent

	field = indent
	directive = indent
	markup = indent


class ValidateReferences(Validator):
	codes = {
		# pylint: disable=unnecessary-lambda
		"unresolved-ref": lambda target: "unresolved reference to {:}".format(target),
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
		cls._fail("unresolved-ref", cls._node_line(node), target="%s:%s" % (node.get("reftype", "dunno"), node.get("reftarget", "dunno2")))
		cls.clear_state()


class ValidateTree(Validator):
	"""
	Enforces specific structural and semantic rules.
	"""
	app = name = doc = None
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
		"concept",
		"command",
		"function",
		"hook",
		"applied",
		"lang",
		"type",
		"operator",
		"topic",
		"guide",
	]
	VALID_TOP_LEVEL_NODES = [
		"index",
		"section",
		"comment",
	] + PRIMARY_DOC_TYPES
	REQUIRED_PRIMARY_CHILDREN = {  # TODO: note that these messages could be combined into a single one: "{:} documents should always include a {:} section"
		"history": rule("fail-future", "{:} documents should have a history section"),
		"seealso": rule("fail-future", "{:} documents should have a seealso section"),
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
	def init_state(cls, app, doctree, docname):  # pylint: disable=arguments-differ
		cls.app = app
		cls.name = docname
		cls.doc = doctree
		DEV_DOCTREES and debug("dev_doctrees:", "full document tree", doctree)

	@classmethod
	def clear_state(cls):  # pylint: disable=arguments-differ
		cls.app = cls.name = cls.doc = None

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
		for node in top.traverse(cls.valid_child, include_self=True):
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


class ValidatePinnedDocs(Validator):
	"""Not actually sharing much code with other validators."""

	# output files "pinned" as reference/test files whose output should not unintentionally slip while we work; as such, we raise hell if they change.
	test_files = [
		# (reference_file_path, built_file_path)
		("hook", "hook/hook"),  # directory
		("master", "master/master"),  # directory
		("predefined", "driver/predefined"),  # concept, macro
		("ed", "LPC/ed"),  # command
		("init", "applied/init"),  # applied
		("input_to", "efun/input_to"),  # efun
		("privilege_violation", "master/privilege_violation"),  # master
		("default_method", "hook/default_method"),  # hook
		("codestyle", "internals/codestyle"),  # meta
		("parsing-inline-closures", "internals/parsing-inline-closures"),  # meta
		("negotiation", "concepts/negotiation"),  # admonition (note, misleading)
		("modifiers", "LPC/modifiers"),  # modifier
		("int", "LPC/int"),  # type
		("foreach", "LPC/foreach"),  # lang, keyword
		("arrow", "LPC/arrow"),  # lang, operator
		("pragma", "LPC/pragma"),  # lang, pragma
		("functionlist", "efun/functionlist"),  # :include:
	]
	test_output_types = ["html", "plain"]

	@classmethod
	def notify_pinned_difference(cls, source, pinned, generated):
		cls.app.env.warn(source,
			"\n".join(
				(
					"Pinned file '{pinned:}' differs from generated '{generated:}'.",
					"	You should manually compare the files in case output has unintentionally changed:",
					"		git diff --no-index --color-words=. {pinned:} {generated:}",
					"	If the output difference is expected, update the pinned file to current output with:",
					"		cp {generated:} {pinned:}"
				)
			).format(pinned=pinned, generated=generated), "*")

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
			# self.diff_doxy(pinned, generated)

		debug("Temporary debug report on which object types are in use", {k: len(v or []) for k, v in app.env.domains['lpc'].data.items()})

		cls.clear_state()


def set_dev_flags(app):
	"""
	Set globals based on develop_options config.

	Intentionally factored these options out into individual binary globals for the small time savings; some of these debug lines will have many thousands of chances to run.

	Note that while these are set here, it's only because we have to wait for Sphinx to set up its environment before we have config values; otherwise they should be treated as constants.
	"""
	# pylint: disable=global-statement
	global DEV_PIN_TEST, DEV_DOCTREES, DEV_PLAINTEXT, DEV_REF, DEV_DOXYGEN
	# a dict is like a fistful of options
	dev = app.config.lddoc_develop_options
	DEV_PIN_TEST = dev["pinned"] or sum(dev.values()) > 0
	DEV_DOCTREES = dev["doctrees"]
	DEV_PLAINTEXT = dev["plaintext"]
	DEV_REF = dev["ref"]
	DEV_DOXYGEN = dev["doxygen"]
	if DEV_PLAINTEXT > 5:
		LPCTextTranslator.__getattribute__ = LPCTextTranslator.report_calls


def heat_lamps(app):
	"""Builder is alive; get conf values & setup."""
	set_dev_flags(app)


def setup(app):
	app.domains = {'std': sphinx.domains.std.StandardDomain}
	app.add_config_value("lddoc_develop_options", False, '')
	app.connect('builder-inited', heat_lamps)
	app.verbosity = 2

	# do_nothing = lambda *x: None
	def do_nothing(*args):
		pass

	app.add_node(
		CrouchingTitle,
		html=(CrouchingTitle.visit_title, do_nothing),
		text=(CrouchingTitle.visit_title, do_nothing),
		doxygen=(CrouchingTitle.visit_title, do_nothing)
	)

	app.add_domain(LPCDomain)
	app.add_domain(LPCAppliedDomain)
	app.add_builder(LPCTextBuilder)
	app.add_builder(LPCDoxygenBuilder)

	# adding admonitions
	app.add_directive("security", LPCSecurityWarning)
	app.add_directive("limit", LPCLimitWarning)
	app.add_directive("stability", LPCStabilityWarning)
	app.add_directive("obsolete", LPCObsoleteWarning)
	app.add_directive("misleading", LPCMisleadingWarning)

	app.set_translator("plain", LPCTextTranslator)
	app.set_translator("html", LPCHTMLTranslator)
	app.set_translator("doxygen", LPCDoxygenTranslator)

	app.add_role('char', char_role)
	app.connect('source-read', ValidateSource.lint)

	app.connect('doctree-resolved', semantic_sibling_section._scrub)
	app.connect('doctree-resolved', ValidateTree.lint)
	app.connect('missing-reference', ValidateReferences.lint)
	app.connect('build-finished', ValidatePinnedDocs.lint)
	app.connect('build-finished', Validator.summary)

	return {
		'version': '0.1',
	}
	# new in 1.3, we can return a dict containing extension metadata; extension 'version', 'parallel_read_safe' and 'parallel_write_safe' (tried this and it borked, but maybe it's fixable)
