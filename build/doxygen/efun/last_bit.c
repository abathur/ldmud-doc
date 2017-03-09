public class efun {
   /**
    * Return the number of the last set bit in bitstring \p str.
    * 
    * Each character contains 6 bits. So you can store a value between 0 and 63 in one character (2^6=64). Starting character is the blank char:` `(U+00020 SPACE) which has the value 0. The first character in the string is the one with the lowest bits (0-5).
    * 
    * @synopsis{
    * int last_bit(string str)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string s;
    * 
    * s = set_bit("", 4);
    * s = set_bit(s, 2);
    * 
    * last_bit(s) // returns 4
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::set_bit(), efun::clear_bit(), efun::next_bit(), efun::test_bit(), efun::count_bits(), efun::and_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
   **/
   int last_bit(string str);
}
