.. type:: int
  :synopsis: An integer.

  .. .. type:: int
    decimal: 1-9[0-9]
    sedecimal: 0x11
    binary: 0b00010001
    octal: 0o21
    char: `<character>`
    test2: 0b00010001

  An integer. Normally full 32 bits signed, yielding a range of at least -2,147,483,648 to 2,147,483,647. The exact available range is given by the predefined macros __INT_MIN__ and __INT_MAX__.

  .. usage::
    Integer values can be specified in decimal, in sedecimal when preceeded by ``0x`` (e.g. ``0x11``), binary when preceeded by ``0b`` (e.g. ``0b00010001``), octal when preceeded by ``0o`` (e.g. ``0o21``) and as character yielding the charset value for the character as the number to use (e.g. ``'0'`` yields ``48`` on ASCII machines).

    Character values are enclosed in single-quotes (``'``), with the sequence ``'''`` returning the single-quote itself. Instead of the literal character an escape-sequence can be written between the single-quotes:

    .. include:: escape_sequences.index

  .. subtopic:: SYNTAX

    .. productionlist::
      integer: `decimalinteger` | `octinteger` | `hexinteger` | `bininteger` | `char`
      decimalinteger: `nonzerodigit` `digit`* | "0"+
      nonzerodigit: "1"..."9"
      digit: "0"..."9"
      octinteger: "0" ("o" | "O") `octdigit`+
      hexinteger: "0" ("x" | "X") `hexdigit`+
      bininteger: "0" ("b" | "B") `bindigit`+
      octdigit: "0"..."7"
      hexdigit: `digit` | "a"..."f" | "A"..."F"
      bindigit: "0" | "1"
      char: "'" `unicode_char` "'"

  .. seealso:: :lang:`types`, :type:`float`, :type:`string`, :modifier:`public`
