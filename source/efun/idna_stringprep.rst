.. efun:: string idna_stringprep(string str, int profile, int flags)
  :include: <idn.h>
  :optional:

  Prepare the UTF-8 string :arg:`str` according to the stringprep :arg:`profile` (see also libidn stringprep(3)).

  .. todo:: should this doc connect the dots a little better? What is libidn? We could at least stick it in the/a glossary and link out?

  :arg:`profile` and :arg:`flags` are one of the values defined in :file:`idn.h`.

  If an error occurs, an exception is thrown.

  The efun is available only if the system supports libidn - in that case :macro:`__IDNA__` is defined.

  :history 3.3.713 introduced:

  .. seealso:: :efun:`convert_charset`, :efun:`idna_to_ascii`, :efun:`idna_to_unicode`
