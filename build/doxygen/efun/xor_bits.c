public class efun {
   /**
    * \p str1 and \p str2 are both bitstrings. The result of the function is a bitstring with the binary-xor of \p str1 and \p str2, ie. a string in which a bit is set only if the corresponding bits in either \p str1 or \p str2 (but not both) is set.
    * 
    * @synopsis{
    * string xor_bits(string str1, string str2)
    * }
    * 
    * @usage{
    * The below example demonstrates how efun::xor_bits() cancels out the bit common to s1 and s2, but retains bits present only in one string:
    * 
    * ~~~{.c}
    * string s1, s2, s3;
    * 
    * s1 = set_bit("", 3);
    * s1 = set_bit(s1, 15);  // s1 is "( (", bits 3 and 15
    * 
    * s2 = set_bit("", 3);
    * s2 = set_bit(s2, 4);   // s2 is "8", bits 3 and 4
    * 
    * s3 = xor_bits(s1, s2); // s3 is "0 (", bits 4 and 15
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::clear_bit(), efun::set_bit(), efun::test_bit(), efun::next_bit(), efun::last_bit(), efun::count_bits(), efun::and_bits(), efun::or_bits(), efun::invert_bits(), efun::copy_bits()
   **/
   string xor_bits(string str1, string str2);
}
