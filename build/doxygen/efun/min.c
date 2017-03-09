public class efun {
   /**
    * Determine the minimum value of the arguments and return it. If called with an array (which must not be empty) as only argument, it returns the minimum value of the array contents.
    * 
    * @synopsis{
    * string min(string arg, ...)
    * string min(string *arg_array)
    * int|float min(int|float arg, ...)
    * int|float min(int|float *arg_array)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * min(1)                     // returns 1
    * min(1, -1.1)               // returns -1.1
    * min("foo", "bar")          // returns "bar"
    * min( ({ "foo", "bar" }) )  // returns "bar"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::max()
   **/
   int|float min(int|float *arg_array);
}
