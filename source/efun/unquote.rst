.. efun:: mixed * unquote(quoted_array)
  string|symbol unquote(symbol)

  Removes a quote from quoted arrays and symbols. When the last quote from a symbol is removed, the result is a string.

  .. usage::

    ::

      unquote('foo)         // returns "foo"
      unquote( '({1,2,3}) ) // returns ({1,2,3})

  :history 3.2.9 introduced:

  .. seealso:: :efun:`quote`, :efun:`symbolp`
