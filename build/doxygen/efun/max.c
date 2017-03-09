public class efun {
   /**
    * Determaxe the maximum value of the arguments and return it. If efun::max() is called with an array (which must not be empty) as only argument, it returns the maximum value of the array contents.
    * 
    * @synopsis{
    * string    max(string arg, ...)
    * string    max(string *arg_array)
    * int|float max(int|float arg, ...)
    * int|float max(int|float *arg_array)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * max(1)                     // returns 1
    * max(1, 1.1)                // returns 1.1
    * max("foo", "bar")          // returns "foo"
    * max( ({ "foo", "bar" }) )  // returns "foo"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::min()
   **/
   int|float max(int|float *arg_array);
}
