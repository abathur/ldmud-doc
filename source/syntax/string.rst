.. type:: string
  literal constructor: ""

  Strings in lpc are true strings, not arrays of characters as in C (and not pointers to strings). Strings are mutable -- that is, the contents of a string can be modified as needed.

  .. todo:: should the above forms include the below in some way?

  The text of a string is written between double-quotes ("). A string can written over several lines when the lineends are escaped (like a macro), however a better solution is to write one string per line and let the gamedriver concatenate them.

  String text typically consists of literal characters, but escape-sequences can be used instead of characters:

    .. todo:: see above

  .. include:: escape_sequences.index

  Adjacent string literals are automatically concatenated by the driver when the LPC program is compiled. String literals joined with '+' are concatenated by the LPC compiler as well.

  .. todo:: syntax section

  .. seealso:: :topic:`types`
