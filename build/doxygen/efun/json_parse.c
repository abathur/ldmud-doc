public class efun {
   /**
    * This efun parses the `JSON` object encoded as string in `jsonstr` into a suitable LPC type.
    * 
    * | json type                   | LPC type     |
    * |-----------------------------|--------------|
    * | @ref driver_syntax_types    | int (0)      |
    * | "null"                      |              |
    * | `boolean`                   | int (0 or 1) |
    * |                             |              |
    * | @ref driver_syntax_int      | int          |
    * | "int" | `int64`             |              |
    * | `double`                    | float        |
    * | @ref driver_syntax_string   | string       |
    * | "string"                    |              |
    * | @ref driver_syntax_object   | mapping      |
    * | "object"                    |              |
    * | @ref driver_syntax_arrays   | arrays       |
    * | "array"                     |              |
    * 
    * @par warning: All other `JSON` types cause a runtime error.
    * 
    * The `JSON` object can nest other `JSON` objects.
    * 
    * The function is available only if the driver is compiled with Iksemel support. In that case, `__JSON__` is defined.
    * 
    * @par limit: 64 bit wide integers can only be parsed losslessly on hosts with a 64 bit wide LPC int and json-c library newer than 0.90.
    * 
    * @par limit: @ref driver_topics_predefined "__FLOAT_MIN__" is not serialized/parsed losslessly.
    * 
    * @synopsis{
    * mixed json_parse(string jsonstring)
    * }
    * 
    * @usage{
    * The following examples demonstrate the LPC values returned by parsing a sample of JSON strings:
    * 
    * ~~~{.c}
    * json_parse("42")                   // 42
    * json_parse("42.0")                 // 42.0
    * json_parse("\"hello world\\n\"")   // "hello world\n"
    * json_parse("[ 1, 2, 3, 4, 5, 6 ]") // ({1,2,3,4,5,6})
    * 
    * json_parse("{ \"test 2\": 42.000000, \"test 1\": 42 }")
    * // ([ "test 1": 42, "test 2": 42.0 ])
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.5.0)
    * }
    * 
    * @see efun::json_serialize()
   **/
   mixed json_parse(string jsonstring);
}
