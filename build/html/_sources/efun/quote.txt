.. efun:: mixed quote(mixed)

Converts arrays to quoted arrays and strings to symbols.
Symbols and quoted arrays get quoted once more.

EXAMPLES
quote("foo") -> 'foo
quote(({1,2,3})) -> '({1,2,3})

.. history
Introduced in 3.2@70

  .. seealso:: :efun:`symbolp`, :efun:`unquote`
