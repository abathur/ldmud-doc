.. efun:: int widthof(mapping map)

  Returns the number of values per key of mapping <map>.
  If <map> is 0, the result is 0.

EXAMPLES
  mapping m = ([ "foo": 1,2 ]);
  widthof(m)  --> returns 2

.. history
  Introduced in LDMud 3.2.6.

  .. seealso:: :efun:`sizeof`, :efun:`mkmapping`, :efun:`m_reallocate`, :efun:`m_values`, :efun:`unmkmapping`
