public class efun {
   /**
    * @synopsis{
    * string sha1(string arg [, int iterations ])
    * string sha1(int  * arg [, int iterations ])
    * }
    * 
   **/
   string sha1(int  * arg [, int iterations ]);
}
DESCRIPTION
Create and return a SHA1 message digest from <arg>.
<arg> may be a string, or an array of numbers (each considered to
be a character, ignoring all but the lowest byte).

If <iterations> is given as a number greater than 0, it is
the number of iterations used in the digest calculation. If omitted,
the driver executes just one iteration.

The efun costs 5 ticks per iteration.

EXAMPLES
string s;

s = sha1("Hello");
s = sha1( ({ 'H', 'e', 'l', 'l', 'o' }) );

Introduced in LDMud 3.3.523.
LDMud 3.3.712 added number arrays as argument, and the number

   of iterations.

LDMud 3.3.717 added the iteration-based evaluation cost.
Since LDMud 3.3.719 obsoleted by hash().

   See Also: 
      efun::crypt(), efun::md5(), efun::md5_crypt(), efun::hash(), efun::hmac()
