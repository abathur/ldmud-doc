public class efun {
   /**
    * Abort execution. If the current program execution was
    * initiated by catch(), that catch expression will
    * return <arg> as error code.
    * 
    * Calling throw() without previous catch() does not make sense
    * and will result in a "Throw with no catch." error.
    * 
    * @synopsis{
    * void throw(mixed arg)
    * }
    * 
    * @usage{
    * This will just print the string "aborting execution":
    * catch(throw("aborting execution"));
    * }
    * 
    * @see efun::catch(), efun::raise_error()
   **/
   void throw(mixed arg);
}
