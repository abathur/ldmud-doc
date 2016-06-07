public class efun {
   /**
    * @synopsis{
    * int test_bit(string str, int n)
    * }
    * 
   **/
   int test_bit(string str, int n);
}
Return 0 or 1 if bit <n> was set in string <str>.

Each character contains 6 bits. So you can store a value
between 0 and 63 in one character (2^6=64). Starting character
is the blank " " which has the value 0. The first character in
the string is the one with the lowest bits (0-5).

EXAMPLES
test_bit("_",5);

Returns 1 because "_" stands for the number 63 and therefore
the 6th bit is set.

test_bit(" ",3);

Returns 0 because " " stands for 0 and no bit is set.

      See Also: 
         efun::set_bit(), efun::clear_bit(), efun::last_bit(), efun::next_bit(), efun::count_bits(),

   efun::and_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
