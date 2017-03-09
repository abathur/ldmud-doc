public class efun {
   /**
    * Abort execution. If the current program execution was initiated by efun::catch(), that catch expression will return arg as error code, else the arg will printed as error message.
    * 
    * This is very similar to efun::throw(), but while efun::throw() is intended to be called inside efun::catch(), efun::raise_error() can be called anywhere. Furthermore, efun::raise_error() includes the complete error handling with generation of a stack backtrace, making it a very expensive function.
    * 
    * @synopsis{
    * void raise_error(string arg)
    * }
    * 
    * @see efun::catch(), efun::throw()
   **/
   void raise_error(string arg);
}
