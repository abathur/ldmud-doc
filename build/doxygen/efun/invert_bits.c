public class efun {
   /**
    * Invert the status of all bits in bitstring \p str and return the new string.
    * 
    * Note that the total number of bits (ie the string length) stays the same.
    * 
    * @synopsis{
    * string invert_bits(string str)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string s;
    * 
    * s = set_bit("", 3);
    * s = set_bit(s, 4);
    * s = set_bit(s, 15); //s is now  "8 ("
    * 
    * invert_bits(s) //returns "G_W"
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::set_bit(), efun::clear_bit(), efun::test_bit(), efun::last_bit(), efun::and_bits(), efun::or_bits(), efun::xor_bits(), efun::count_bits(), efun::copy_bits()
   **/
   string invert_bits(string str);
}
