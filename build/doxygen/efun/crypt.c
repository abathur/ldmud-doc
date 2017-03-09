public class efun {
   /**
    * Crypt the string \p str the first two characters from the string \p seed as a seed. If \p seed is an integer, then a random seed is used.
    * 
    * The result has the first two characters as the seed.
    * 
    * If you want to let users enter password information without echo, efun::input_to() can be used with the `INPUT_NOECHO` flag.
    * 
    * @synopsis{
    * string crypt(string str, int seed)
    * string crypt(string str, string seed)
    * }
    * 
    * @see efun::md5(), efun::md5_crypt(), efun::sha1(), efun::hash(), efun::hmac()
   **/
   string crypt(string str, string seed);
}
