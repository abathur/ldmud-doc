.. efun:: string idna_to_unicode(string name)
  :include: <idn.h>
  :optional:

Convert string <name> from idna representation (8z punycode)
to UTF-8.

If an error occurs, an exception is thrown.

The efun is available only if the system supports libidn - in
that case __IDNA__ is defined.

.. history
Introduced in LDMud 3.3.713.

  .. seealso:: :efun:`convert_charset`, :efun:`idna_to_ascii`, :efun:`idna_stringprep`
