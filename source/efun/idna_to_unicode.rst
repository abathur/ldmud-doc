.. efun:: string idna_to_unicode(string name)
  :include: <idn.h>
  :optional:

  Convert string :arg:`name` from idna representation (8z punycode) to UTF-8.

  If an error occurs, an exception is thrown.

  The efun is available only if the system supports libidn - in that case :macro:`__IDNA__` is defined.

  :history 3.3.713 introduced:

  .. seealso:: :efun:`convert_charset`, :efun:`idna_to_ascii`, :efun:`idna_stringprep`
