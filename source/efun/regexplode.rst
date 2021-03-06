.. efun:: string * regexplode(string text, string pattern)
  string * regexplode(string text, string pattern, int opt)
  :include: <regexp.h>

  This function is similar to explode but accepts a regular expression :arg:`pattern` as delimiter (interpreted according to :arg:`opt` if given).

  If flag :macro:`RE_OMIT_DELIM` is not set in :arg:`opt`, then every second element in the result vector will be the text that matched the delimiter. If the flag is set, then the result vector will contain only the text between the delimiters.

  .. usage::

    ::

      regexplode("abcdef", "cde")                // ({ "ab", "cde", "f" })
      regexplode("abcdef", "cde", RE_OMIT_DELIM) // ({ "ab", "f" })

  :history 3.2@61 introduced:
  :history 3.3 changed: added the optional :arg:`opt` argument and the :macro:`RE_OMIT_DELIM` flag.
  :history 3.5.0 changed: an error is raised if :macro:`RE_PCRE` is specified in :arg:`opt`, but the driver lacks PCRE support.

  .. seealso:: :efun:`explode`, :efun:`regexp`, :efun:`regmatch`, :efun:`regreplace`, :efun:`regexp_package`, :concept:`regexp`
