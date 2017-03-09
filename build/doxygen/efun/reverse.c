public class efun {
   /**
    * Reverse the content of array or string \p arg and return the result. If \p arg is an integer, the bits in the integer are reversed.
    * 
    * If called in the reference variant, the argument array itself is reversed and then returned.
    * 
    * @par limit: Reference ranges like `reverse(&(a[1..2]))` are not supported.
    * 
    * @synopsis{
    * int reverse(int arg)
    * string  reverse(string arg)
    * mixed * reverse(mixed * arg)
    * mixed * reverse(mixed * & arg)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * reverse(0x306a) // returns 0x560c0000
    * 
    * reverse("test") // returns "tset"
    * 
    * mixed * arr = ({ 1, 2 });
    * reverse(arr)  // returns ({ 2, 1 }), leaves arr unchanged.
    * reverse(&arr) // returns ({ 2, 1 }), sets arr to ({ 2, 1 })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.529)
    * changed (3.3.532) -- added the reversal of bits in an integer.
    * }
    * 
   **/
   mixed * reverse(mixed * & arg);
}
