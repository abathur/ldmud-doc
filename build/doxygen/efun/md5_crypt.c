public class efun {
   /**
    * @synopsis{
    * string md5_crypt(string str, int seed)
    * string md5_crypt(string str, string seed)
    * }
    * 
   **/
   string md5_crypt(string str, string seed);
}
Crypt the string <str> the first two characters
from the string <seed> as a seed. If <seed> is an integer, then
a random seed is used.

The result has the first two characters as the seed.

The efun uses the MD5 algorithm for encryption, and the result
is compatible with the Apache password encryption.

If you want to let enter password information without echo,
input_to() can be used with special argument.

Introduced in LDMud 3.3

   See Also: 
      efun::crypt(), efun::input_to(), efun::md5(), efun::md5_crypt(), efun::hash(), efun::hmac()
