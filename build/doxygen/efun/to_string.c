public class efun {
   /**
    * @synopsis{
    * string to_string(mixed)
    * (string)<value>()
    * }
    * 
   **/
   (string)<value>();
}
DESCRIPTION
The argument is converted to a string. Works with int, float,
object, arrays, structs, symbols, strings and closures.

Converts closures and structs into an appropriate name (this
has mostly debugging purposes).

CAVEAT: Arrays are considered exploded strings, ie. arrays of char
codes, and are 'imploded' up to the first non-number entry, whatever
comes first. That means that to_string(({ 49, 50 })) will return
"12" and not "({ 49, 50 })".

BUGS
The cast notation only works if the precise type of <value>
is known at compile-time. This will not be fixed - use the
function form instead.

LDMud 3.2.8 adds lambda closures to the accepted data types.
LDMud 3.3.250 adds structs to the accepted data types.

   See Also: 
      efun::to_array(), efun::to_int(), efun::to_object(), efun::to_struct(), efun::sprintf()
