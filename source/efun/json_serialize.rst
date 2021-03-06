.. efun:: string json_serialize(mixed data)
  :optional:
  :experimental:

  This efun creates a :topic:`JSON` object from the given LPC variable and returns the object encoded as a LPC string. For container types like arrays, mappings and structs, this will be done recursively.

  Only the following LPC types are serialized. All other LPC types cause a runtime error.

  =========  =====================
  LPC type   :topic:`JSON` type
  =========  =====================
  <int>      :topic:`JSON` int
  <float>    :topic:`JSON` double
  <string>   :topic:`JSON` string
  <mapping>  :topic:`JSON` objects
  <array>    :topic:`JSON` arrays
  <struct>   :topic:`JSON` objects
  =========  =====================

  The function is available only if the driver is compiled with Iksemel support. In that case, :macro:`__JSON__` is defined.

  .. limit:: Only mappings with a width of 1 value per key and only string keys can be serialized.

  .. limit:: 64 bit wide integers can only be serialized losslessly on hosts with a 64 bit wide LPC int and json-c library newer than 0.90.

  .. limit:: :macro:`__FLOAT_MIN__` is not serialized/parsed losslessly.

  .. usage::

    The examples below demonstrate the :topic:`JSON` strings serialized from simple LPC values::

      json_serialize(42)              // "42"
      json_serialize(42.0)            // "42.0"
      json_serialize("hello world\n") // "\"hello world\\n\""
      json_serialize(({1,2,3,4,5,6})) // "[ 1, 2, 3, 4, 5, 6 ]"

      json_serialize(([ "test 1": 42, "test 2": 42.0 ]))
      // "{ \"test 2\": 42.000000, \"test 1\": 42 }"

  :history 3.5.0 introduced:

  .. seealso:: :efun:`json_parse`
