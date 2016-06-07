public class efun {
   /**
    * @synopsis{
    * void raise_error(string arg)
    * }
    * 
   **/
   void raise_error(string arg);
}
Abort execution. If the current program execution was
initiated by catch(), that catch expression will return arg as
error code, else the arg will printed as error message.

This is very similar to throw(), but while throw() is intended to be
called inside catch(), raise_error() can be called anywhere.
Furthermore, raise_error() includes the complete error handling
with generation of a stack backtrace, making it a very expensive
function.

   See Also: 
      efun::catch(), efun::throw()
