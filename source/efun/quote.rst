.. efun:: mixed quote(mixed)

  Converts arrays to quoted arrays and strings to symbols. Symbols and quoted arrays get quoted once more.

  .. usage::

    ::

      quote("foo") -> 'foo
      quote(({1,2,3})) -> '({1,2,3})

  :history 3.2@70 introduced:

  .. seealso:: :efun:`symbolp`, :efun:`unquote`
