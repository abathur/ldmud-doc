.. efun:: int rmember(mixed *array, mixed elem [, int start])
  int rmember(string s, int elem [, int start])

For arrays and strings, returns the index of the last
occurance of second arg in the first arg, or -1 if none found.
If <start> is given and non-negative, the search starts at
that position.

.. history
Introduced in LDMud 3.2.10.
LDMud 3.3.556 added the <start> parameter.

  .. seealso:: :efun:`member`
