public class efun {
   /**
    * \p str1 and \p str2 are both bitstrings. The result of the function is a bitstring with the binary-and of \p str1 and \p str2, ie. a string in which a bit is set only if both corresponding bits in the input strings are set, too.
    * 
    * @synopsis{
    * string and_bits(string str1, string str2)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string s1, s2, s3;
    * 
    * s1 = set_bit("", 3); s1 = set_bit(s1, 15);  -> s1 is "( ("
    * s2 = set_bit("", 3); s2 = set_bit(s2, 4);   -> s2 is "8"
    * 
    * s3 = and_bits(s1, s2);
    * 
    * -> s3 is now "8", ie. a bitstring with bit 3 set only.
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::clear_bit(), efun::set_bit(), efun::test_bit(), efun::next_bit(), efun::last_bit(), efun::count_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
   **/
   string and_bits(string str1, string str2);
}
