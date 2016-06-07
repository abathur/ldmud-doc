public class efun {
   /**
    * @synopsis{
    * int next_bit(string str, int start)
    * }
    * 
   **/
   int next_bit(string str, int start);
}
int next_bit (string str, int start, int find_cleared)

DESCRIPTION
Return the number of the next bit in bitstring <str> after position
<start>. Usually this is the next set bit, but if <find_cleared>
is given and not 0, the position of the next cleared bit is returned.

Note that finding cleared bits after the last set bit is limited to
the actual length of <str>.

Each character contains 6 bits. So you can store a value
between 0 and 63 in one character (2^6=64). Starting character
is the blank " " which has the value 0. The first character in
the string is the one with the lowest bits (0-5).

EXAMPLES
string s;
int p;

s = set_bit("", 4); s = set_bit(s, 2);

for (p = -1; -1 != (p = next_bit(s, p); )
   write(p+"n");

--> will write 2 and 4

   See Also: 
      efun::set_bit(), efun::clear_bit(), efun::test_bit(), efun::last_bit(), efun::count_bits(), efun::and_bits(), efun::or_bits(), efun::xor_bits(), efun::invert_bits(), efun::copy_bits()
