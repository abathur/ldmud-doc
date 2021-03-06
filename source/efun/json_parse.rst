.. efun:: mixed json_parse(string jsonstring)
  :optional:
  :experimental:

  This efun parses the :topic:`JSON` object encoded as string in :arg:`jsonstr` into a suitable LPC type.

  ===========================  ========
  json type                    LPC type
  ===========================  ========
  :type:`null`                 int (0)
  :type:`boolean`              int (0 or 1)
  :type:`int` | :type:`int64`  int
  :type:`double`               float
  :type:`string`               string
  :type:`object`               mapping
  :type:`array`                arrays
  ===========================  ========

  .. warning:: All other :topic:`JSON` types cause a runtime error.

  The :topic:`JSON` object can nest other :topic:`JSON` objects.

  The function is available only if the driver is compiled with Iksemel support. In that case, :macro:`__JSON__` is defined.

  .. limit:: 64 bit wide integers can only be parsed losslessly on hosts with a 64 bit wide LPC int and json-c library newer than 0.90.

  .. limit:: :macro:`__FLOAT_MIN__` is not serialized/parsed losslessly.

  .. usage::

    The following examples demonstrate the LPC values returned by parsing a sample of JSON strings::

      json_parse("42")                   // 42
      json_parse("42.0")                 // 42.0
      json_parse("\"hello world\\n\"")   // "hello world\n"
      json_parse("[ 1, 2, 3, 4, 5, 6 ]") // ({1,2,3,4,5,6})

      json_parse("{ \"test 2\": 42.000000, \"test 1\": 42 }")
      // ([ "test 1": 42, "test 2": 42.0 ])

  :history 3.5.0 introduced:

  .. seealso:: :efun:`json_serialize`
