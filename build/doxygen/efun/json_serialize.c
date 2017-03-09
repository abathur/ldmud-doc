public class efun {
   /**
    * This efun creates a `JSON` object from the given LPC variable and returns the object encoded as a LPC string. For container types like arrays, mappings and structs, this will be done recursively.
    * 
    * Only the following LPC types are serialized. All other LPC types cause a runtime error.
    * 
    * | LPC type  | `JSON` type           |
    * |-----------|-----------------------|
    * | <int>     | `JSON` int            |
    * | <float>   | `JSON` double         |
    * | <string>  | `JSON` string         |
    * | <mapping> | `JSON` objects        |
    * |           |                       |
    * | <array>   | `JSON` arrays         |
    * | <struct>  | `JSON` objects        |
    * 
    * The function is available only if the driver is compiled with Iksemel support. In that case, `__JSON__` is defined.
    * 
    * @par limit: Only mappings with a width of 1 value per key and only string keys can be serialized.
    * 
    * @par limit: 64 bit wide integers can only be serialized losslessly on hosts with a 64 bit wide LPC int and json-c library newer than 0.90.
    * 
    * @par limit: @ref driver_topics_predefined "__FLOAT_MIN__" is not serialized/parsed losslessly.
    * 
    * @synopsis{
    * string json_serialize(mixed data)
    * }
    * 
    * @usage{
    * The examples below demonstrate the `JSON` strings serialized from simple LPC values:
    * 
    * ~~~{.c}
    * json_serialize(42)              // "42"
    * json_serialize(42.0)            // "42.0"
    * json_serialize("hello world\n") // "\"hello world\\n\""
    * json_serialize(({1,2,3,4,5,6})) // "[ 1, 2, 3, 4, 5, 6 ]"
    * 
    * json_serialize(([ "test 1": 42, "test 2": 42.0 ]))
    * // "{ \"test 2\": 42.000000, \"test 1\": 42 }"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.5.0)
    * }
    * 
    * @see efun::json_parse()
   **/
   string json_serialize(mixed data);
}
