.. efun:: int widthof(mapping map)

  Returns the number of values per key of mapping :arg:`map`. If :arg:`map` is 0, the result is 0.

  .. usage::

    ::

      mapping m = ([ "foo": 1,2 ]);
      widthof(m) // returns 2

  :history 3.2.6 introduced:

  .. seealso:: :efun:`sizeof`, :efun:`mkmapping`, :efun:`m_reallocate`, :efun:`m_values`, :efun:`unmkmapping`
