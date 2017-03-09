public class efun {
   /**
    * Create and return a SHA1 message digest from `arg`. `arg` may be a string, or an array of numbers (each considered to be a character, ignoring all but the lowest byte).
    * 
    * If `iterations` is given as a number greater than 0, it is the number of iterations used in the digest calculation. If omitted, the driver executes just one iteration.
    * 
    * The efun costs 5 ticks per iteration.
    * 
    * @synopsis{
    * string sha1(string arg [, int iterations ])
    * string sha1(int  * arg [, int iterations ])
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string s;
    * 
    * s = sha1("Hello");
    * s = sha1( ({ 'H', 'e', 'l', 'l', 'o' }) );
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.523)
    * changed (3.3.712) -- added number arrays as argument, and the number of iterations.
    * changed (3.3.717) -- added the iteration-based evaluation cost.
    * deprecated (3.3.719) -- obsoleted by hash().
    * }
    * 
    * @see efun::crypt(), efun::md5(), efun::md5_crypt(), efun::hash(), efun::hmac()
   **/
   string sha1(int  * arg [, int iterations ]);
}
