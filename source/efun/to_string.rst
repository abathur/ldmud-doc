.. efun:: string to_string(mixed)
  (string)<value>

  The argument is converted to a string. Works with int, float, object, arrays, structs, symbols, strings and closures.

  Converts closures and structs into an appropriate name (this has mostly debugging purposes).

  .. warning:: Arrays are considered exploded strings, ie. arrays of char codes, and are 'imploded' up to the first non-number entry, whatever comes first. That means that ``to_string(({ 49, 50 }))`` will return ``12`` and not ``({ 49, 50 })``.

  .. limit:: The cast notation only works if the precise type of <value> is known at compile-time. This will not be fixed--use the function form instead.

  :history 3.2.8 changed: adds lambda closures to the accepted data types.
  :history 3.3.250 changed: adds structs to the accepted data types.

  .. seealso:: :efun:`to_array`, :efun:`to_int`, :efun:`to_object`, :efun:`to_struct`, :efun:`sprintf`
