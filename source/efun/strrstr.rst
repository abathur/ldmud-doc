.. efun:: int strrstr(string str, string str2)
  int strrstr(string str, string str2, int pos)

  Returns the index of the first occurence of :arg:`str2` in :arg:`str` searching from position :arg:`pos` (default: ``-1 == string end``) on backward. In other words: the index of the last occurance of :arg:`str2` before the given position :arg:`pos`.

  The returned index is relative to the beginning of the string.

  If :arg:`str2` is not found in :arg:`str`, -1 is returned.

  If :arg:`pos` is negative, it designates the start position relative to the end of the string (the search will still proceed towards the beginning of the string).

  :history 3.2.10 introduced:

  .. seealso:: :efun:`strstr`, :efun:`strlen`, :efun:`sscanf`, :efun:`sprintf`, :efun:`explode`
