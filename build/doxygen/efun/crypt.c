public class efun {
   /**
    * Crypt the string <str> the first two characters
    * from the string <seed> as a seed. If <seed> is an integer, then
    * a random seed is used.
    * 
    * The result has the first two characters as the seed.
    * 
    * If you want to let enter password information without echo,
    * input_to() can be used with special argument.
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
