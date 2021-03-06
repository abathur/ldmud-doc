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
from docutils.parsers.rst.directives import admonitions, parts
from sphinx.writers.text import TextTranslator, TextWrapper
from sphinx.writers.html import SmartyPantsHTMLTranslator
import operator
import itertools
import sys

import string
import copy
import validators
from collections import defaultdict, OrderedDict, Iterable

# true constants
MAXWIDTH = 78  # wrap docs at

# global vars for gatekeeping development output; these are named like constants but we can't actually set values until Sphinx parses the config; see set_dev_flags()
DEV_DOXYGEN = None
DEV_PLAINTEXT = None
DEV_REF = None
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


class CrouchingTitle(nodes.title, nodes.Invisible):
	"""
	Non-rendering title node.

	Fulfills docutils/sphinx expectations for where title nodes are in a document, but allows us to have things like SYNOPSIS appear to be the title. Mostly necessary so that our TOC/link entries show the right title.
	"""

	def visit_title(self, node):  # pylint: disable=unused-argument, no-self-use
		raise nodes.SkipNode()


# TODO: something in here works fine for the history/typedfield kind, but falls flat on the include/groupedfield kind. The basics work now, but I either need to move the node, or figure out how to parse it out in a separate step when I parse out the synopsis.
# TODO: support repeating an argument to document different types (i.e., the format of arg X when both array or mapping are valid)
class LPCDocFieldTransformer(DocFieldTransformer):
	lint = validators.Usage

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
				new_list.append(entry)
				pseudo_field = False
			else:
				fieldtype, content = entry
				field_name = fieldtype.name
				if isinstance(fieldtype, PseudoField):
					pseudo_field = True

				fieldtypes = types.get(fieldtype.name, {})

				new_list.append(fieldtype.make_field(fieldtypes, self.domain, content, self.lint, node))


		node.replace_self(new_list if pseudo_field else nodes.field_list("", *new_list, id=field_name))



# two classes below violate normal class naming standard in order to uphold docutils idiomatic naming for node classes.
class semantic_sibling_section(nodes.section):  # pylint: disable=invalid-name
	"""
	Node that stands in for a sub-section, but gets rendered at parents indentation.

	Allows us to nest something like a seealso directive under the element it refers to, but not get another level of indentation tacked on in output.
	"""
	valid_builders = ["multi", "html", "plain", "doxygen"]

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
	def make_field(self, types, domain, items, lint, parent):
		def handle_item(fieldarg, content):
			line = nodes.line()
			line += self.make_xref(
				self.rolename,
				domain,
				fieldarg.split()[-1],  # differ +: .split()[-1]
				addnodes.literal_strong
			)
			if fieldarg in types:
				line += nodes.Text(' (')
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
								line += self.make_xref(self.typerolename, domain, "".join(token), addnodes.literal_emphasis)
								token = []
							line += nodes.Text(char, char)

					if len(token):
						line += self.make_xref(self.typerolename, domain, "".join(token), addnodes.literal_emphasis)
					# end all lines differ
				else:
					line += fieldtype
				line += nodes.Text(')')
			line += nodes.Text(' -- ')
			line += content
			return line

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
	valid_verbs = ["introduced", "backported", "changed", "deprecated", "removed"]
	lint_codes = {
		"history-verb": lambda verb: "{:} is not a valid history verb".format(verb)
	}

	def make_field(self, types, domain, items, lint, parent):
		node = semantic_sibling_section(ids=[self.cap_tag])  # TODO: correct IDs?
		node.tagname = self.tagname

		if lint:
			lint.init_state(parent, self.lint_codes)
			node.line = lint.lineno

		# VERBATIM FROM sphinx.util.docfields.TypedField unless otherwise noted
		def handle_item(fieldarg, content):
			par = nodes.generated()
			verb = fieldarg.split()[-1]
			if verb not in self.valid_verbs:
				lint._fail("history-verb", lint.lineno, verb=verb)
			# TODO: not sure this should still be an xref
			par += self.make_xref(self.rolename, domain, verb, addnodes.literal_strong)  # differ +: .split()[-1]
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

		title = nodes.title('', self.label, meta=True)  # differs: field_name -> title
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
		if lint:
			lint.clear_state()
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


class LPCSecurityWarning(admonitions.Warning):
	node_class = security


class LPCLimitWarning(admonitions.Warning):
	node_class = limit


class LPCStabilityWarning(admonitions.Warning):
	node_class = stability


class LPCObsoleteWarning(admonitions.Warning):
	node_class = obsolete


class LPCMisleadingWarning(admonitions.Warning):
	node_class = misleading


class LPCObject(c.CObject):
	"""Base directive class for LPC-specific directives."""
	status_options = ["optional", "deprecated","experimental"]
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
	objtype = domain = indexnode = names = env = top_level = topics = None

	option_spec = {
		# document status
		"optional": lambda x: "OPTIONAL",
		"deprecated": lambda x: "DEPRECATED",
		"removed": lambda x: "REMOVED", # TODO: rm?
		"experimental": lambda x: "EXPERIMENTAL",
		# other things
		"name": directives.unchanged,
		"title": directives.unchanged,
		"synopsis": directives.unchanged,
		"include": directives.unchanged,
		"topics": directives.unchanged  # add to this index?
	}
	option_spec.update(c.CObject.option_spec)
	csplit_re = re.compile(r',\s*')
	wsplit_re = re.compile(r'')

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
		optiondesc = ", ".join([self.options[x] for x in self.status_options if x in self.options])
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
		#self.names = set() # TODO: don't think this is necessary anymore but disabling may cause hell

		if out_node:
			self._parse_node_meta(out_node)

		self.topics = self.get_topics()
		for topic in self.topics:
			self.env.domaindata['lpc']['topics'][topic].append(self.env.docname)

		# TODO: given below note, this may be pointless since we aren't planning on using the directive form, I don't think; disable it and see what breaks?
		if self.names:
			# needed for association of version{added,changed} directives
			self.env.temp_data['object'] = self.names[0]

	def _parse_type(self, attach_to, ctype):  # pylint: disable=unused-argument
		# add cross-ref nodes for all words
		parts = c.wsplit_re.split(ctype)
		last = len(parts) - 1
		for i, part in enumerate(parts):
			if not part:
				continue

			tnode = nodes.Text(part, part)
			if i != last and part[0] in string.ascii_letters + '_' and part not in self.stopwords:
				pnode = addnodes.pending_xref(
					'', refdomain='lpc', reftype="any", reftarget=part, modname=None, classname=None, refdoc=self.env.docname)
				pnode += tnode
				attach_to += pnode
			elif part[0] == "*":
				pnode = addnodes.pending_xref(
					'', refdomain='lpc', reftype='type', reftarget="array", modname=None, classname=None, refdoc=self.env.docname)
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
		synopsis += nodes.title(text=self.synopsis_title + self.get_status_desc(), meta=True)
		return synopsis

	def _parse_synopsis_syntax(self, synopsis_node, out_node):  # pylint: disable=unused-argument
		if "title" in self.options:
			out_node["title"] = self.options["title"]
			synopsis_node += nodes.field_list('',
				nodes.field('',
					nodes.field_name(self.arguments[0], self.arguments[0]),
					nodes.field_body("", nodes.inline("", self.options["title"]))
				)
			)
		else:
			out_node["title"] = self.arguments[0]
			synopsis_node += nodes.container("", nodes.Text(self.arguments[0], self.arguments[0]))

	def _parse_synopsis(self, out_node):
		synopsis_node = self.get_synopsis_node()

		self._parse_synopsis_syntax(synopsis_node, out_node)

		out_node += synopsis_node

	def get_content_node(self):  # pylint: disable=no-self-use
		"""Return the node the directive's primary content should be attached to."""
		content = nodes.section(ids=["DESCRIPTION"])  # TODO: IDs
		content += nodes.title(text="DESCRIPTION", meta=True)
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
		if "topics" in self.options:
			return self.csplit_re.split(self.options["topics"])
		return []

	def add_local_target(self, name, signode):
		local_targetname = "{:}.{:}".format(self.env.docname, name)
		self.env.domaindata['lpc']["arg"][local_targetname] = True
		self.state.document.note_anonymous_target(signode)

	def add_target(self, name, signode):
		set_source_info(self, signode)
		targetname = 'lpc.{:}.{:}'.format(self.objtype, name)

		if targetname not in self.state.document.ids:
			signode['first'] = (not len(signode['names']))
			signode['names'].append(targetname)
			signode['ids'].append(targetname)

			# We can only have one explicit target for a node, but sometimes we want more (i.e., we might refer to the -> operator or the arrow operator) so we use anonymous targets for the rest...
			if signode['first']:
				self.state.document.note_explicit_target(signode)
			else:
				self.state.document.note_anonymous_target(signode)

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
		if self.noindex:
			return

		indextext = self.get_index_text(name)
		if indextext:
			# from docs; index is a list of 5-tuples of ``(entrytype, entryname, target, ignored, key)``.
			self.indexnode['entries'].append(('single', indextext, targetname, '', ''))
			self.indexnode['entries'].append(('single', self.objtype + "; " + indextext, targetname, '', ''))
			# TODO: this might be the place (or the source of the information with which) to schlorp up the "topics" that docs will get collected into:
				# any time we have more than N of the same tag, it gets a topic page (and we maybe even have a build error until we add one)
			for topic in self.topics:
				self.indexnode['entries'].append(('single', topic + "; " + indextext, targetname, '', ''))

	def add_target_and_index(self, name, sig, signode):
		self.add_index(self.add_target(name, signode), name)

	def get_out_node(self):  # pylint: disable=no-self-use
		"""Returns the node that will represent this directive, to which all of its other output will be attached."""
		return nodes.section(ids=sorted(set(self.names)) if self.names else self.name)  # TODO: this was just ["glossary"], but I'm not sure .names is "right" yet

	def preparse(self):
		self.top_level = isinstance(self.state.parent, nodes.document)
		self.indexnode = addnodes.index(entries=[])
		self.names = []

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
		self.preparse()
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
		# TODO: this may be dumb.
		if title and len(title):
			out_node += nodes.title("", "", *self.state.inline_text(title, self.lineno)[0])
			out_node['ids'] = [title]
			if 'synopsis' in self.options:
				out_node += nodes.block_quote("", nodes.paragraph("", "", *self.state.inline_text(self.options['synopsis'], self.lineno)[0]))
		elif 'synopsis' in self.options:
			out_node += nodes.paragraph("", "", *self.state.inline_text(self.options['synopsis'], self.lineno)[0])
			#nodes.paragraph("", "", *self.state.inline_text(self.arguments[0], self.lineno)[0])

		original = sphinx.domains.std.Glossary.run(self)
		# sphinx applies a glossary class here, which they style in a specific way that makes each term very bold; let's take another swing at it.
		original[-1][0]["classes"].remove("glossary")
		for indexnode in original[-1].traverse(addnodes.index):
			indexnode.parent.remove(indexnode)
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
			see_aslan = nodes.title(text="SEE ALSO", meta=True)
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

# TODO: would be nice to have a way to set style wrappers per re-use of this meta type
class LPCVar(LPCObject):
	"""Conceptually similar to LPCObject, but for smaller things (i.e., no separate sections). Could use a more generic/re-usable name."""

	varnames = []

	def get_out_node(self):
		return nodes.definition_list_item(ids=self.varnames)  # TODO: ids?

	def get_synopsis_node(self):
		return nodes.term("", ", ".join(self.varnames))

	def _parse_synopsis_syntax(self, synopsis_node, out_node):
		for var in self.varnames:
			#debug("TRYING TO ADD", var)
			self.add_target_and_index(var, None, synopsis_node)

	def get_content_node(self):
		return nodes.definition()

	@staticmethod
	def _clean_macro_args(line):
		open_paren = line.find("(")
		if open_paren > -1:
			return "{:}()".format(line[:open_paren])
		return line

	def run(self):
		#print(self.arguments)
		self.varnames = [self._clean_macro_args(x) for x in self.arguments[0].splitlines()]
		indexnode, out_node = super().run()
		return [indexnode, nodes.definition_list("", out_node)]


# TODO: light-weight way to generate these?
class LPCUsage(LPCObject):
	required_arguments = 0

	def run(self):
		temp = nodes.section(ids=["USAGE"])
		temp.tagname = "usage"
		temp += nodes.title(text="USAGE", meta=True)
		self.state.nested_parse(self.content, self.content_offset, temp)
		return [temp]


class LPCLore(LPCObject):
	required_arguments = 0

	def run(self):
		temp = semantic_sibling_section(ids=["LORE"])  # TODO: ids
		temp += nodes.title(text="LORE", meta=True)
		self.state.nested_parse(self.content, self.content_offset, temp)
		return [temp]

import unicodedata

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

		objtype = self.objtype
		self.objtype = "function"
		fullname = super().handle_signature(sig, signode)
		self.objtype = objtype

		# add refs to args
		for param in signode.traverse(addnodes.desc_parameter):
			#print("TRAVERSING PARAM", param, param[-1].astext(), param[-1].astext().lstrip(" *"))
			self.add_local_target("arg.{:}".format(unicodedata.normalize("NFKD", param[-1].astext()).strip(" *.")), param)

		return None, fullname

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

	# I AM FIGURING OUT HOW TO TITLE PROPERLY
	# TODO: if 'names' can be added before or after this code, this could easily add names and just call super()._parse_synopsis(out_node); everything else is the same.
	def _parse_synopsis(self, out_node):

		synopsis = self.get_synopsis_node()

		#self.names = set() # TODO: don't think this is necessary anymore but disabling may cause hell

		self._parse_synopsis_syntax(synopsis, out_node)

		out_node += synopsis

	def _parse_meta(self, out_node=None):
		super()._parse_meta(out_node)


# TODO: is there a better way to do this?
class LPCSyntaxIndex(Index):  # pylint: disable=too-few-public-methods
	name = "syntaxindex"
	localname = "localsyntaxindex"
	shortname = "shortsyntaxindex"

	def gen_keyword(self, name, docname, anchor):
		out = []
		out.append([name, 0, docname, anchor, None, None, self.domain.data['summaries'].get("lpc.keyword."+name, None)])
		return out

	def gen_operator(self, name, docname, anchor):
		out = []
		out.append([name, 0, docname, anchor, None, None, self.domain.data['summaries'].get("lpc.operator."+name, None)])
		return out

	# TODO: kill one of these
	def gen_operator2(self, name, docname, anchor):
		out = []
		out.append([name, 0, docname, anchor, None, None, self.domain.data['summaries'].get("lpc.operator."+name, None)])
		for syntax in self.domain.data['variants'].get(name, ()):
			out.append([syntax, 2, None, None, None, None, ''])
		return out

	def generate(self, docnames=None):
		collapse = False
		content = []
		last_letter = None

		choices = (0,1,2)

		import random

		for part, label, fn in (
			("keyword", "keywords", self.gen_keyword), # would actually like to include all types and modifiers (or have a separate all keywords section which does?)
			("operator", "operators", self.gen_operator), # the name should be the literal operator, comma-delimited examples in extra, could use qualifier for a category, could also generate nested/child entries for the examples, i.e.
			# foreach
			# 	foreach(ex1)
			# 	foreach(ex2)
			# 	foreach(ex3)
			# This kinda implies each syntax form would get its own directive?
			("type", "types", self.gen_keyword),
			("modifier", "modifiers", self.gen_keyword),
			("syntax", "other syntax", self.gen_keyword)):
			content.append((label, []))

			for name in sorted(self.domain.data[part], key=str.lower):
				docname, anchor = self.domain.data[part][name]

				content[-1][1].extend(fn(name, docname, anchor))

		return (content, collapse)


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

			# This abysmally documented format is kinda free-form in a way (you can make whatever values you like here, as long as you update the template to use them), but the base html template uses (and Alabaster inherits) the following form:
			# (name, grouptype, page, anchor, extra, qualifier, description)
			# name: the visible index entry text
			# grouptype:
			# 	affects how entries are grouped, only used values are 1 or 2
			# 	1 - toggleable group "head"
			# 	2 - indented group member
			# 	Any other value will just produce a regular entry (which can also appear as a group head, you just won't be able to toggle the group closed/open)
			# page: the doc/path this will link to
			# anchor: any #anchor indicated in the link
			# extra: this appears in parenthesis immediately after the name
			# qualifier: immediately before the description, in bold, terminated with a colon.
			# description: about like you'd expect
			entries = [name, 0, docname, anchor, None, None, self.domain.data['summaries'].get("lpc.hook."+hook_name, None)]
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
		out_node += nodes.title(text=self.arguments[0])

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
		# TODO: this probably overrides/obsoletes every other use of 	 since it happens on init
		self.synopsis_title = self.name.upper()

	def get_out_node(self):
		topic = nodes.section(ids=sorted(set(self.names)))
		topic += CrouchingTitle(text=self.names[0])
		return topic

	def preparse(self):
		super().preparse()
		self._preparse_names()

	def _preparse_names(self):
		self.names.append(self.arguments[0])
		if "name" in self.options:
			self.names.append(self.options["name"])

	def run(self):
		out_node = super().run()

		# no point in making multiple targets at the same loc for the same name
		for name in sorted(set(self.names)):
			self.add_target_and_index(
				name, None, out_node[1]
			)
		return out_node


class LPCCommand(LPCTopic):

	# commands can have multiple forms; don't want all of them as the title
	def get_out_node(self):
		topic = nodes.section(ids=[self.arguments[0]])
		topic += CrouchingTitle(text=self.arguments[0].split()[0])
		return topic


class LPCXRefRole(c.CXRefRole):
	pass


class LPCGuide(LPCTopic):
	"""
	Pared down directive class omits the synopsis parsing/section and collapses the content parse so that there's no a separate/child "DESCRIPTION" node/section.
	"""

	def get_out_node(self):
		topic = nodes.section(ids=sorted(set(self.names)))
		topic += nodes.title(text="Guide to {:}".format(self.arguments[0]))
		return topic

	def _parse_content(self, out_node):  # pylint: disable=unused-argument

		self.before_content()
		self.state.nested_parse(self.content, self.content_offset, out_node)

		LPCDocFieldTransformer(self).transform_all(out_node)

		self.env.temp_data['object'] = None  # TODO: this value is set in _parse_meta, and may be going away...
		self.after_content()

	def run(self):
		self.preparse()
		out_node = self.get_out_node()

		# adding an option for the Contents directive to self (and clearing args) in order to pass this object through that directive, then re-set arguments.
		self.options['local'] = True
		temp = self.arguments
		self.arguments = None
		out_node += directives.parts.Contents.run(self)[0]
		self.arguments = temp

		self._parse_meta(out_node)
		self._parse_content(out_node)

		for name in sorted(set(self.names)):
			self.add_target_and_index(
				name, None, out_node[1]
			)

		return [out_node]


# TODO: probably a better way to handle
class LPCLang(LPCTopic):
	required_arguments = 1  # TODO: why?


def syntax_highlight(highlight_regexi):
	return re.compile("({:})".format("|".join(highlight_regexi.splitlines())))


class LPCSyntax(LPCLang):
	synopsis_title = "SYNTAX"
	variants = []
	syntax = None
	usage = None
	lines = None
	show_usage_name = True

	option_spec = {
		"highlighters": syntax_highlight
	}
	option_spec.update(LPCLang.option_spec)

	# doc_field_types = [
	# 	LPCTypedField(
	# 		'keywords',
	# 		label=l_('Keywords'),
	# 		names=('keyword', 'keyword'),
	# 		typerolename='type',
	# 		typenames=('type',)
	# 	),
	# 	LPCTypedField(
	# 		'terms',
	# 		label=l_('Terms'),
	# 		names=('term', 'term'),
	# 		typerolename='type',
	# 		typenames=('type',)
	# 	),
	# ]
	# doc_field_types.extend(LPCLang.doc_field_types)

	# TODO: something here needs to add us to the syntax index, ideally under an appropriate subhead
	#
	# TODO: ideally factor out getting the title node in LPCObject so that other types can fiddle with it easily
	def get_synopsis_node(self):
		if self.top_level:
			synopsis = nodes.section(ids=[self.synopsis_title])  # TODO: fix ids
			# TODO: below was text="SYNTAX"
			synopsis += nodes.title(text=self.synopsis_title + self.get_status_desc(), meta=True)
			return synopsis
		else:
			return nodes.container(ids=[self.synopsis_title])

	def _parse_synopsis_syntax(self, synopsis_node, out_node):
		self.parse_syntax(synopsis_node)

	def _preparse_long_usage(self):
		self.usage = []
		indent = 0

		if 'name' in self.options:
			self.usage.append(nodes.Text(self.syntax+'\n'))

		for label, body in map(self.use_parts, self.lines[1:]):
			if label:
				indent = 4
				if not len(self.usage):
					self.usage.append(addnodes.literal_strong('', '{:}:\n'.format(label)))
				# all labels after the first get a blank preceding line
				else:
					self.usage.append(addnodes.literal_strong('', '\n{:}:\n'.format(label)))

			#ideally we should nest everything until the next label if we encounter one
			self.usage.append(nodes.Text(" "*indent))
			self.usage.extend(body)
			self.usage.append(nodes.Text("\n"))

		if len(self.usage) > 1:
			self.usage.pop()

	def get_usage_name(self):
		if 'title' in self.options:
			return self.options['title'].capitalize()
		elif 'name' in self.options:
			return self.options['name'].capitalize()
		else:
			return self.syntax.capitalize()

	label_regex = re.compile("(?<!\\\):\s?")
	#need to be able to tailor this to the long/short modes which now need different nodes...

	def use_parts(self, example):
		use_nodes = []

		label_check = self.label_regex.split(example.strip(), 1)

		if len(label_check) == 1:
			body = label_check[0].replace('\:', ':')
			label = None
		else:
			label, body = label_check

		# highlight
		# TODO: catch regex errors and log a lint failure?
		highlighter = self.options["highlighters"] if "highlighters" in self.options else re.compile("({:})".format(re.escape(self.syntax)))

		for i, part in enumerate(highlighter.split(body)):
			if i % 2 and len(part): # odd (highlight)
				use_nodes.append(nodes.inline(part, part, classes=["highlighted"]))
			else: # even (Text)
				use_nodes.append(nodes.Text(part))

		return label, use_nodes

	def use_parts2(self, example):
		use_nodes = []

		label_check = example.split(":", 1) if not example.startswith(' ') else [example]

		label = label_check[0].strip() if len(label_check) > 1 else None

		label_check[-1] = label_check[-1].strip() if label else label_check[-1][2:].rstrip()

		for i, part in enumerate(label_check[-1].partition(self.syntax)):
			if i % 2 and len(part): # odd (highlight)
				use_nodes.append(nodes.inline(part, part, classes=["highlighted"]))
			else: # even (Text)
				use_nodes.append(nodes.Text(part))

		return label, use_nodes

	def _preparse_short_usage(self):
		fields = [addnodes.literal_strong('', self.get_usage_name()+': '), nodes.literal('', self.syntax)]

		# let's only keep this if we have no sub-labels, see end of function
		field = nodes.line_block()

		fields.append(field)

		# 1. replace on each line
		# 2. parse on each line
		# 3. wrap each line in a literal
		# 4. throw in text separator nodes

		for label, body in map(self.use_parts, self.lines[1:]):
			if not label:
				# attach this to the previous field body's line block
				field.append(nodes.line('', '', nodes.literal('', *body)))

			else:
				fields.append(addnodes.literal_strong('', label+':'))
				field = nodes.line_block('', nodes.line('', '', nodes.literal('', *body)))
				fields.append(field)

		if len(fields) == 3: # no sub-labels
			self.usage = fields
		else:
			self.usage = fields[3:]

	def _preparse_usage(self):
		template = None

		if self.top_level:
			self._preparse_long_usage()
		else:
			self._preparse_short_usage()

	def _preparse_syntax(self):

		self.lines = self.arguments[0].splitlines()
		self.syntax = self.lines[0] #TODO this is only right when we name first, not use the syntax unit first
		self._preparse_usage()

	def _preparse_names(self):
		self._preparse_syntax()
		self.names.append(self.syntax)

		if "name" in self.options:
			self.names.append(self.options["name"])

	def parse_syntax(self, synopsis_node):  # pylint: disable=no-self-use
		self.env.domaindata['lpc']['variants'][self.syntax] = self.lines[1:]
		#synopsis_node.append(nodes.literal(self.syntax, self.syntax))

		# Saving this for now in case I later need the knowledge--it was hard to track down.
		# TODO: move somewhere more durable
		# if 'name' in self.options:
		# 	viewlist = ViewList()
		# 	viewlist.append("", "")
		# 	viewlist.append(".. productionlist::", "")
		# 	# TODO: really only want to append objtype for subtypes of syntax (i.e., we want arrow_operator instead of just arrow, but just block instead of block_syntax? Do we really want for_keyword though? maybe this is a new option (production_name or w/e))
		# 	viewlist.append("  {:}_{:}: {:}".format(self.options['name'], self.objtype, self.syntax), "")
		# 	viewlist.append("", "")
		# 	self.state.nested_parse(viewlist, 2, synopsis_node)

		if self.usage:
			if self.top_level:
				#syntax_nodes, messages = self.state.inline_text(self.usage, self.lineno)
				#synopsis_node.append(nodes.literal_block(self.usage, '', *syntax_nodes))
				if self.show_usage_name:
					synopsis_node.append(addnodes.literal_strong('', self.get_usage_name()))
				# the sphinx html formatter uses code highlighting unless node.rawsource != node.astext(), so we have to specifiy a filler rawtext string to avoid a trip through the lexer
				litblock = nodes.literal_block('filler', '', *self.usage)
				synopsis_node.append(litblock)
			else:
				synopsis_node.extend(self.usage)
		else:
			pass


	def get_out_node(self):
		if self.top_level:
			return super().get_out_node()
		else:
			return nodes.container()  # TODO: IDs

	def get_content_node(self):
		if self.top_level:
			return super().get_content_node()
		else:
			return nodes.definition(ids=["DESCRIPTION"])  # TODO: IDs


class LPCOperator(LPCSyntax):

	#detect unnamed condition and capitalize below / invert the presentation order:
	# Equality operator: =
	# , operator:
	# Operator: ,
	def get_usage_type(self):
		return ' operator'

	def get_usage_name(self):
		if 'name' in self.options:
			return '{:} operator'.format(self.options['name'].capitalize())
		else:
			return 'Operator'

class LPCKeyword(LPCSyntax):

	#detect unnamed condition and capitalize below / invert the presentation order:
	# Equality operator: =
	# , operator:
	# Operator: ,
	# TODO: lolwut?
	def get_usage_type(self):
		return ' HAMoperator'

	def get_usage_name(self):
		return 'Keyword'


class LPCType(LPCSyntax):
	show_usage_name = False


# note: we declare some generic objects and some specific objects based on those in object_types, directives and roles below; the specific types are listed under the generic type (with an extra indent) in order to suggest these relationships
# TODO: either undo above, or re-eval for correctness; this has all evolved a lot
class LPCDomain(c.CDomain):
	name = 'lpc'
	label = 'LPC'

	from docutils.parsers.rst import roles

	# TODO: figure out what this is for (i.e., resolve the nagging concern I have stomped all over its purpose; I know it's for localization, roughly, just not sure on specifics)
	object_types = {
		'topic': ObjType(l_('topic'), 'topic'),
			'overview': ObjType(l_('overview'), 'overview'),
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
			'overview': LPCTopic,
		'lang': LPCLang,
			'syntax': LPCSyntax,
				'keyword': LPCKeyword,
					'modifier': LPCVar,
					'type': LPCType,
				'operator': LPCOperator,
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
		#'usage': LPCObject,
		'lore': LPCLore,
		'var': LPCObject,
		'enumerate': LPCGlossary,
		'meta': LPCTopic,
	}
	roles = {
	# presentation
		'highlight': roles.CustomRole(
			'highlight',
			roles.GenericRole('highlight', nodes.inline),
			{'classes':['highlighted']}
		),
	# semantic
		'topic': LPCXRefRole(),  # innernodeclass=nodes.strong),
			'overview': LPCXRefRole(),
		'lang': LPCXRefRole(),  # innernodeclass=nodes.inline),
			'syntax': LPCXRefRole(),
				'keyword': LPCXRefRole(),
					'modifier': LPCXRefRole(),
					'type': LPCXRefRole(),
				'operator': LPCXRefRole(),
			'pragma': LPCXRefRole(),
		'function': LPCXRefRole(),
			'arg': LPCXRefRole(),
			'part': LPCXRefRole(),
			'applied': LPCXRefRole(),
			'efun': LPCXRefRole(),
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
		"arg": {},
		"part": {},
		"efun": {},
		"command": {},
		"overview": {},
		"enumerate": {},  # TODO: needed? presently no entries
		"glossary": {},  # TODO: needed? presently no entries (esp given above?)
		"guide": {},
		"meta": {},
		"hook": {},
		"macro": {},
		"master": {},
		"objects": {},
		"topic": {},
		'lang': {},
			'syntax': {},
				'keyword': {},
					'modifier': {},
					'type': {},
				'operator': {},
			'pragma': {},
		'var': {},  # TODO: needed? presently no entries

		"summaries": {},
		"variants": {},
		"topics": defaultdict(list),
	}
	indices = [LPCSyntaxIndex, LPCHookIndex]  # TODO: eval whether we still need this hookindex, whether we're using it, and whether we need some other kinds of index that we don't have already; keeping it for now, just so we have an example of a separate index and how to make one; AFAIK nothing links directly to this atm

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

	# TODO: factor resolve_xref and resolve_any_xref to kill duplication

	def resolve_xref(self, env, fromdocname, builder, typ, target, node, contnode):  # pylint: disable=too-many-arguments
		"""Return a resolved refnode or none."""

		if typ == "any":
			results = self.resolve_any_xref(env, fromdocname, builder, target, node, contnode)
			if len(results):
				return results[0][1]
			else:
				return None

		DEV_REF > 1 and debug("DEV_REF: attempting to resolve xref",
			{"env": env},
			{"fromdocname": fromdocname},
			{"builder": builder},
			{"typ": typ},
			{"target": target},
			{"node": node, "refdomain": node['refdomain'] if 'refdomain' in node else None},
			{"contnode": contnode}
		)

		title = target
		# strip pointer asterisk
		target = target.rstrip(' *')
		target_sans = target.partition("(")[0]
		specifier = None

		if typ in self.directives and typ in self.data:
			if target_sans in self.data[typ]:
				specifier = 'lpc.{:}.{:}'.format(typ, target_sans)
				target = target_sans
			elif target in self.data[typ]:
				specifier = 'lpc.{:}.{:}'.format(typ, target)
			else:
				return None

		elif typ in self.roles:
			if typ in self.data:
				# we're tracking this typ and it resolves
				local_refname = '{:}.{:}.{:}'.format(fromdocname, typ, target_sans)
				#print("LOCAL?", local_refname)
				if local_refname in self.data["arg"]:
					refnode = make_refnode(builder, fromdocname, fromdocname, local_refname, contnode, title)
					refnode['section'] = typ
					refnode['fromdoc'] = fromdocname
					refnode['todoc'] = fromdocname
					return refnode

				else:
					local_refname = '{:}.{:}.{:}'.format(fromdocname, typ, target)
					if local_refname in self.data["arg"]:
						refnode = make_refnode(builder, fromdocname, fromdocname, local_refname, contnode, title)
						refnode['section'] = typ
						refnode['fromdoc'] = fromdocname
						refnode['todoc'] = fromdocname
						return refnode

				print("NON-RESOLVED ROLE FOR ", local_refname)

				return None
			else:
				# should this be logged/warned/errored?
				return None
		elif target in self.data["objects"]:
			if typ not in self.directives: # not sure if this happens, but it should probably be some sort of error if it do...
				print("UNRECOGNIZED REF TYP", typ)
			# or the target was in our fallback 'objects'
			typ = "objects"
			specifier = 'lpc.{:}.{:}'.format(typ, target)
		else:
			return None
		obj = self.data[typ][target]

		refnode = make_refnode(builder, fromdocname, obj[0], specifier, contnode, title)
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

		# TODO: list of refs we'll bother identifying without providing the type; this could be liberal for easy references, or very tightly controlled to require doc source be more semantic
		for typ in ["type", "keyword", "modifier", "syntax", "efun", "hook", "master", "lang", "guide", "objects"]:
			if typ in self.data and target in self.data[typ]:
				obj = self.data[typ][target]
				refnode = make_refnode(builder, fromdocname, obj[0], 'lpc.{:}.{:}'.format(typ, target), contnode, target)
				refnode['section'] = obj[1]
				refnode['fromdoc'] = fromdocname
				refnode['todoc'] = obj[0]
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


# TODO: For organizational clarity it might be useful to factor a few of the bigger sections, such as the desc functions, out into a mixin
# docutils uses two catch-all functions for raising errors on unimplemented visit/depart; pylint likes to complain, but we shouldn't implement them  # pylint: disable=abstract-method
class LPCHTMLTranslator(SmartyPantsHTMLTranslator):  # pylint: disable=abstract-method
	# pylint: disable=unused-argument
	# TODO: update per reorg
	SECTIONS = {
	# TODO: update these when the dust settles
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
		self.required_params_left = sum([isinstance(c, addnodes.desc_parameter) for c in node.children])
		self.param_separator = node.child_text_separator

	def depart_desc_parameterlist(self, node):
		if not self.tabling:
			return super().depart_desc_parameterlist(node)
		self.body.append('<td colspan="1000" style="border:0;padding:0;margin:0;text-align:right;"><span class="sig-paren">)</span></td>')

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

	# override to remove the title node this builder adds to keep the tree clean
	def depart_admonition(self, node=None):
		super().depart_admonition(node)
		node.pop(0)


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
	# TODO: update to sanely reflect simpler organization
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
			# bullet list
			self.end_state(first='- ', end=None)
		elif self.list_counter[-1] == -2:
			# definition list
			pass
		else:
			# enumerated list
			self.end_state(first='%s. ' % self.list_counter[-1], end=None)

	def depart_bullet_list(self, node):
		# If we aren't part of some structure that needs preserving (for now just list_item), add a blank line after bullet lists; TODO: may need this elsewhere, or it may cause problems elsewhere.
		if not isinstance(node.parent, nodes.list_item):
			self.states[-1].append((0, ['']))
		return super().depart_bullet_list(node)

	def visit_caption(self, node):
		self.new_state(0)

	def depart_caption(self, node):
		self.add_text("_:")
		self.end_state(first="_", end=None)
		self.add_text(self.nl)

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
		# debug(
		# 	"DEV_PLAINTEXT",
		# 	"called %s.%s" % (self.__class__, name)
		# )
		returned = object.__getattribute__(self, name)
		debug(
			"DEV_PLAINTEXT",
			"called",
			name,
			returned
		)
		return returned


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

	def nowrap_add_text(self, text):
		"""Replace all spaces with non-breaking spaces."""
		return self.old_add_text(text)

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

	def build_arg(self, node):
		argdesc = node[5].astext() if isinstance(node[5], nodes.Text) else "\n".join(self._consume_node(node[5], self._prefix))
		# print("BUILD ARG", node, repr(argdesc))
		# for index, part in enumerate(node):
		# 	print("ARG PARTS", index, part, part.__class__)
		name = node[0].astext()
		return "{}@param {} {}".format(self._prefix, name, argdesc)

	def build_args2(self, node):
		"""Convert from Sphinx to Doxygen idioms for arg/param lists."""

		# plaintext is like: value (closure) -- mixed <closure>(object blueprint, string objectname)
		# where everything after "--" is the description, so it's <name> (<type>) -- <desc>
		return [self.build_arg(x) for x in node.traverse(nodes.line)]

	def build_args(self, node):
		args = []
		for arg in node.traverse(nodes.line):
			name = arg[0].astext()
			if isinstance(arg[5], nodes.Text):
				args.append("@param {} {}".format(name, arg[5].astext()))
			else:
				args.append("@param {}".format(name))
				args.extend(self._consume_node(arg[5], ""))

		return [self._prefix + x for x in args]

	def build_topical_doc(self, node):
		self._set_prefix("", 3)

		# build doc parts
		# make this an ordered dict, pre-build the part in order
		parts = OrderedDict()
		parts["definition"] = None
		parts["synopsis"] = None
		parts["arguments"] = None
		parts["description"] = None
		parts["usage"] = None
		parts["history"] = None
		parts["seealso"] = None

		# TODO: update after culling/refining directives


		for section in node.traverse(nodes.section):
			if "DESCRIPTION" in section["ids"]:
				parts["description"] = section
			elif len(set(["SYNOPSIS", "HOOK", "TOPIC", "COMMAND", "OVERVIEW", "LANG", "TYPE", "SYNTAX", "KEYWORD", "MODIFIER", "OPERATOR", "META", "GUIDE"]).intersection(set(section["ids"]))):
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
				parts["arguments"].append("")
				fieldlist.parent.remove(fieldlist)

		# in doxygen output our synopsis is much lower in the document:
		# description
		# synopsis * with 0 args, parenthesis is left off; check html/plain outputs for same
		# usage
		# history
		# seealso *

		# late parse of description after children are pulled out
		if parts["description"]:
			parts["description"] = self.build_description(parts["description"])

		doc = [(0, part) for section, part in parts.items() if part]

		self.states[-1].extend(doc)

	def build_guide_doc(self, node):
		self._set_prefix("", 3)

		# build doc parts
		# make this an ordered dict, pre-build the part in order
		parts = OrderedDict()
		parts["definition"] = None
		parts["synopsis"] = None
		parts["description"] = []

		# TODO: update after culling/refining directives

		for section in node.traverse(nodes.topic):
			if "contents" in section["ids"]:
				section.parent.remove(section)

		parts["synopsis"], parts["definition"] = self.build_guide_synopsis(section)
		for child in node.children:
			if child:
				parts["description"].extend(self.build_description(child))

		doc = [(0, part) for section, part in parts.items() if part]

		self.states[-1].extend(doc)

	def build_function_doc(self, node):
		self._set_prefix(" * ", 3)

		# build doc parts
		# make this an ordered dict, pre-build the part in order
		parts = OrderedDict()
		parts["description"] = None
		parts["synopsis"] = None
		parts["arguments"] = None
		parts["usage"] = None
		parts["history"] = None
		parts["seealso"] = None
		parts["definition"] = None

		# RESUME: The issue here is that my "tagname" changes don't survive the deepcopy before the node reaches this point, BUT just removing the elements seems to cause downstream trouble with them being absent elsewhere. One issue is that any builder following this one ends up getting doctrees with elements already removed. A separate but similar issue is that the plaintext and doxygen builds are turning up with spurious admonition titles in them (because the html builder injects it)...

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
				parts["arguments"].append("")
				fieldlist.parent.remove(fieldlist)

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

	def _consume_node(self, node, prefix=None):
		self.new_state(0)
		node.walkabout(self)
		if prefix is None:
			prefix = self._prefix
		return [
			prefix + (" " * (indent - self._offset)) + line
			for indent, lines in self.states.pop() if len(lines)
			for line in lines
		]

	def build_description(self, node):
		return self._consume_node(node)

	def build_usage2(self, node):
		usage = ["@usage{"]
		# usage.extend([x.astext().splitlines() for x in node[1:-1]])
		for child in node[1:]:
			usage.extend(child.astext().splitlines())
		usage.extend(["}", ""])
		return [self._prefix + x for x in usage]

	def build_usage(self, node):
		usage = ["@usage{"]
		usage.extend(self._consume_node(node, ""))
		usage.extend(["}", ""])
		return [self._prefix + x for x in usage]

	def build_history(self, node):
		history = ["@history{"]
		history.extend([x.astext() for x in node.traverse(nodes.list_item)])
		history.extend(["}", ""])
		return [self._prefix + x for x in history]

	def build_ref(self, node):
		section = node.get("section")
		#print("BUILD_REF", node, section)
		if section in ["efun", "applied", "master"]:
			return "{0}::{1}()".format(section, node.get("reftitle"))
		elif section == "arg":
			return "\p {0}".format(node.get("reftitle"))
		elif section == "part":
			return "\a {0}".format(node.get("reftitle"))
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

	def build_guide_synopsis(self, node):
		desc = node.parent["title"] if "title" in node else None
		docpath = self.builder.current_docname.split("/")
		title = "{0} {{#driver_{1}}}".format(desc or docpath[-1], "_".join(docpath))
		self.builder.out_suffix = ".md"
		return None, [title, "=" * len(title)]

	def build_topic_synopsis(self, node):
		desc = node.parent["title"] if "title" in node.parent else None
		synopsis = self.build_synopsis(node)
		docpath = self.builder.current_docname.split("/")
		# print("DOLL PARTS", node, node.parent, desc, synopsis, docpath)
		title = "{0} {{#driver_{1}}}".format(desc or docpath[-1], "_".join(docpath))
		self.builder.out_suffix = ".md"
		return [self._prefix + x for x in synopsis] if synopsis else None, [title, "=" * len(title)]

	def build_function_synopsis(self, node):
		synopsis = self.build_synopsis(node)
		self.builder.out_suffix = ".c"
		# return [" * " + x for x in synopsis], ["*/"] + [sig + ";" for sig in signatures]
		return [self._prefix + x for x in synopsis], ["**/"] + [synopsis[-3] + ";"]

	def visit_section(self, node):
		if node.tagname in ["function", "applied", "efun", "master"]:
			# skip the node and dive off into our own processing routine
			self.build_function_doc(node)
			raise nodes.SkipNode
		elif node.tagname in ["guide"]:
			self.build_guide_doc(node)
			raise nodes.SkipNode
		elif node.tagname in ["hook", "topic", "command", "overview", "lang", "type", "syntax", "keyword", "modifier", "operator", "meta"]:
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
		if 'meta' in node and node['meta']:
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
			self.add_text("@par %s: " % name)
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

	def depart_table(self, node):
		# type: (nodes.Node) -> None
		lines = None                # type: List[unicode]
		lines = self.table[1:]      # type: ignore
		fmted_rows = []             # type: List[List[List[unicode]]]
		colwidths = None            # type: List[int]
		colwidths = self.table[0]   # type: ignore
		realwidths = colwidths[:]
		separator = 0
		# don't allow paragraphs in table cells for now
		for line in lines:
			if line == 'sep':
				separator = len(fmted_rows)
			else:
				cells = []  # type: List[List[unicode]]
				for i, cell in enumerate(line):
					par = self.wrapper(cell, width=colwidths[i])
					if par:
						maxwidth = max(column_width(x) for x in par)
					else:
						maxwidth = 0
					realwidths[i] = max(realwidths[i], maxwidth)
					cells.append(par)
				fmted_rows.append(cells)

		def writesep(char='-'):
			# type: (unicode) -> None
			out = ['|']  # type: List[unicode]
			for width in realwidths:
				out.append(char * (width + 2))
				out.append('|')
			self.add_text(''.join(out) + self.nl)

		def writerow(row):
			# type: (list[List[unicode]]) -> None
			lines = itertools.zip_longest(*row)
			for line in lines:
				out = ['|']
				for i, cell in enumerate(line):
					if cell:
						adjust_len = len(cell) - column_width(cell)
						out.append(' ' + cell.ljust(
							realwidths[i] + 1 + adjust_len))
					else:
						out.append(' ' * (realwidths[i] + 2))
					out.append('|')
				self.add_text(''.join(out) + self.nl)

		for i, row in enumerate(fmted_rows):
			if i == 1:
				writesep('-')
			writerow(row)

		self.table = None
		self.end_state(wrap=False)


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


def summarize_targets(app, doctree):
	for thing, node in (doctree.ids.items() if "ids" in doctree else []):

		try:
			first = node.next_node(nodes.paragraph, siblings=True)
			# dumbfire; split on first period and call everything before the summary (implies summative first sentences should be mandatory...)
			summary = "".join(first.astext().partition(".")[:2])
			app.env.domaindata['lpc']['summaries'][thing] = summary

		except (ValueError, AttributeError) as e:
			pass
			#print("ValueError on next_node", e, thing, node, doctree, doctree.__dict__)


def set_dev_flags(app):
	"""
	Set globals based on develop_options config.

	Intentionally factored these options out into individual binary globals for the small time savings; some of these debug lines will have many thousands of chances to run.

	Note that while these are set here, it's only because we have to wait for Sphinx to set up its environment before we have config values; otherwise they should be treated as constants.
	"""
	# pylint: disable=global-statement
	global DEV_PLAINTEXT, DEV_REF, DEV_DOXYGEN, DEV_DATA
	# a dict is like a fistful of options
	dev = app.config.lddoc_develop_options
	DEV_PLAINTEXT = dev["plaintext"]
	DEV_REF = dev["ref"]
	DEV_DATA = dev["data"]
	DEV_DOXYGEN = dev["doxygen"]
	if DEV_PLAINTEXT > 5:
		LPCTextTranslator.__getattribute__ = LPCTextTranslator.report_calls
	if False and DEV_DOXYGEN:
		LPCDoxygenTranslator.__getattribute__ = LPCDoxygenTranslator.report_calls


def heat_lamps(app):
	"""Builder is alive; get conf values & setup."""
	set_dev_flags(app)


def lights_out(app, exception):
	#print("SUMMARIES", app.env.domaindata['lpc']['summaries'])
	validators.Topics.lint(app, exception)
	validators.PinnedDocs.lint(app, exception)
	validators.Validator.summary(app, exception)


import multi


def setup(app):
	app.domains = {'std': sphinx.domains.std.StandardDomain}
	app.add_config_value("lddoc_develop_options", False, '')
	app.connect('builder-inited', heat_lamps)
	app.connect('builder-inited', validators.heat_lamps)
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
	app.add_builder(LPCTextBuilder)
	app.add_builder(LPCDoxygenBuilder)
	multi.setup(app)

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
	#TODO: move all of these out into a function in validators?
	#app.connect('source-read', validators.Source.lint)

	app.connect('doctree-read', summarize_targets)

	app.connect('doctree-resolved', semantic_sibling_section._scrub)
	app.connect('build-finished', lights_out)
	# env-purge-doc(app, env, docname)
	# app.connect('env-purge-doc', validators.Validator._purge_doc)

	#print([(x, y) for x, y in app._listeners['doctree-read'].items()])

	return {
		'version': '0.1',
	}
	# new in 1.3, we can return a dict containing extension metadata; extension 'version', 'parallel_read_safe' and 'parallel_write_safe' (tried this and it borked, but maybe it's fixable)
