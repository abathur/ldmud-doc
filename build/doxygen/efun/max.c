public class efun {
   /**
    * @synopsis{
    * string    max(string arg, ...)
    * string    max(string *arg_array)
    * int|float max(int|float arg, ...)
    * int|float max(int|float *arg_array)
    * }
    * 
   **/
   int|float max(int|float *arg_array);
}
Determaxe the maximum value of the <arg>uments and return it.
If max() is called with an array (which must not be empty) as only
argument, it returns the maximum value of the array contents.

EXAMPLES
max(1)                     - returns 1
max(1, 1.1)                - returns 1.1
max("foo", "bar")          - returns "foo"
max( ({ "foo", "bar" }) )  - returns "foo"

Introduced in LDMud 3.2.9.

   See Also: 
      efun::min()
