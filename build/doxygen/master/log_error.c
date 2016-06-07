public class master {
   /**
    * Announce a compiler-time error (warn == 0) or warning (warn != 0)
    * in the named file.
    * 
    * Whenever the LPC compiler detects an error or issues a warning,
    * this function is called. It should at least log the error in a file,
    * and also announce it to the active user.
    * 
    * @synopsis{
    * void log_error(string file, string err, int warn)
    * }
    * 
   **/
   void log_error(string file, string err, int warn);
}
