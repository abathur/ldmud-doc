public class efun {
   /**
    * Abort execution. If the current program execution was initiated by efun::catch(), that catch expression will return \p message as error code.
    * 
    * Calling `throw()` without an enclosing `catch()` does not make sense and will result in a "Throw with no catch." error.
    * 
    * @synopsis{
    * void throw(mixed message)
    * }
    * 
    * @usage{
    * This will just print the string "aborting execution":
    * 
    * ~~~{.c}
    * catch(throw("aborting execution"));
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::catch(), efun::raise_error()
   **/
   void throw(mixed message);
}
