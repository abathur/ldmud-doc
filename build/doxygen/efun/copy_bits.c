public class efun {
   /**
    * Copy the bitrange `[<em>srcstart</em>..<em>srcstart</em>+<em>copylen</em>]` from bitstring \p src and copy it into the bitstring `dest` starting at `deststart`, overwriting the original bits at those positions.
    * 
    * The resulting combined string is returned, the input strings remain unaffected.
    * 
    * If `srcstart` is not given, \p src is copied from the start. If `srcstart` is negative, it is counted from one past the last set bit in the string (ie. '-1' will index the last set bit).
    * 
    * If `deststart` is not given, `dest` will be overwritten from the start. If `deststart` is negative, it is counted from one past the last set bit in the string (ie. '-1' will index the last set bit).
    * 
    * If `copylen` is not given, it is assumed to be infinite, ie. the result will consist of `dest` up to position `deststart`, followed by the data copied from \p src. If `copylen` is negative, the function will copy the abs(`copylen`) bits _before_ `srcstart` in to the result.
    * 
    * None of the range limits can become negative.
    * 
    * @synopsis{
    * string copy_bits(string src, string dest[, int srcstart [, int deststart [, int copylen ]]])
    * }
    * 
    * @usage{
    * ~~~{.c}
    * copy_bits(src, dest, 10)    === src[10..]
    * copy_bits(src, dest, 10, 5) === dest[0..4] + src[10..]
    * copy_bits(src, dest, 10, 5, 3)
    *                             === dest[0..4] + src[10..12] + dest[8..]
    * 
    * ~~~
    * (The src[]/dest[] is just for explanatory purposes!)
    * 
    * }
    * 
    * @history{
    * introduced (3.3.166)
    * }
    * 
    * @see efun::clear_bit(), efun::set_bit(), efun::test_bit(), efun::next_bit(), efun::last_bit(), efun::count_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::and_bits()
   **/
   string copy_bits(string src, string dest[, int srcstart [, int deststart [, int copylen ]]]);
}
