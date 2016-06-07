public class efun {
   /**
    * @synopsis{
    * string copy_bits(string src, string dest[, int srcstart [, int deststart [, int copylen ]]])
    * }
    * 
   **/
   string copy_bits(string src, string dest[, int srcstart [, int deststart [, int copylen ]]]);
}
Copy the bitrange [<srcstart>..<srcstart>+<copylen>[ from
bitstring <src> and copy it into the bitstring <dest> starting
at <deststart>, overwriting the original bits at those positions.

The resulting combined string is returned, the input strings remain
unaffected.

If <srcstart> is not given, <src> is copied from the start.
If <srcstart> is negative, it is counted from one past the last set
bit in the string (ie. '-1' will index the last set bit).

If <deststart> is not given, <dest> will be overwritten from the start.
If <deststart> is negative, it is counted from one past the last set
bit in the string (ie. '-1' will index the last set bit).

If <copylen> is not given, it is assumed to be infinite, ie. the result
will consist of <dest> up to position <deststart>, followed by
the data copied from <src>.
If <copylen> is negative, the function will copy the abs(<copylen>)
bits _before_ <srcstart> in to the result.

None of the range limits can become negative.

EXAMPLES
copy_bits(src, dest, 10)    === src[10..]
copy_bits(src, dest, 10, 5) === dest[0..4] + src[10..]
copy_bits(src, dest, 10, 5, 3)

      === dest[0..4] + src[10..12] + dest[8..]

   (The src[]/dest[] is just for explanatory purposes!)

Introduced in LDMud 3.3.166.

   See Also: 
      efun::clear_bit(), efun::set_bit(), efun::test_bit(), efun::next_bit(), efun::last_bit(), efun::count_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::and_bits()
