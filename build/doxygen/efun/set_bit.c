public class efun {
   /**
    * Return the new string where bit \p n is set in string \p str. Note that the old string \p str is not modified.
    * 
    * Each character contains 6 bits. So you can store a value between 0 and 63 in one character (2^6=64). Starting character is the blank char:` `(U+00020 SPACE) which has the value 0. The first charcter in the string is the one with the lowest bits (0-5).
    * 
    * The new string will automatically be extended if needed.
    * 
    * @synopsis{
    * string set_bit(string str, int n)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string s;
    * s=set_bit("?",5);
    * 
    * ~~~
    * Because "?" has a value of 31 the variable s will now contain the character "_" which is equal to 63 (31+2^5=63):
    * 
    * ~~~{.c}
    * string s;
    * s=set_bit("78",3);
    * s=set_bit(s,8);
    * //s will now contain the string "?<".
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::clear_bit(), efun::last_bit(), efun::next_bit(), efun::test_bit(), efun::count_bits(), efun::and_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
   **/
   string set_bit(string str, int n);
}
