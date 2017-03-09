public class efun {
   /**
    * Count the number of set bits in bitstring \p str and return the number as result.
    * 
    * @synopsis{
    * int count_bits(string str)
    * }
    * 
    * @usage{
    * Here's a very simple example:
    * 
    * ~~~{.c}
    * string s;
    * 
    * s = set_bit("", 3);
    * s = set_bit(s, 15);
    * 
    * count_bits(s) // returns 2
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::clear_bit(), efun::set_bit(), efun::test_bit(), efun::next_bit(), efun::last_bit(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
   **/
   int count_bits(string str);
}
