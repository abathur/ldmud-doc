public class efun {
   /**
    * Return 0 or 1 if bit \p n was set in string \p str.
    * 
    * Each character contains 6 bits. So you can store a value between 0 and 63 in one character (2^6=64). Starting character is the blank char:` `(U+00020 SPACE) which has the value 0. The first character in the string is the one with the lowest bits (0-5).
    * 
    * @synopsis{
    * int test_bit(string str, int n)
    * }
    * 
    * @usage{
    * The below returns 1 because "_" stands for the number 63 and therefore the 6th bit is set:
    * 
    * ~~~{.c}
    * test_bit("_",5);
    * 
    * ~~~
    * The next example returns 0 because char:` `(U+00020 SPACE) stands for 0 and no bit is set:
    * 
    * ~~~{.c}
    * test_bit(" ",3);
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::set_bit(), efun::clear_bit(), efun::last_bit(), efun::next_bit(), efun::count_bits(), efun::and_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
   **/
   int test_bit(string str, int n);
}
