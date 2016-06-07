public class efun {
   /**
    * @synopsis{
    * int time()
    * }
    * 
   **/
   int time();
}
Return number of seconds elapsed since 1. Jan 1970, 0.0:0 GMT.

The time is based on the time provided by the host system, but
the driver does make sure the result of time() is monotonically
increasing (ie. changes only to bigger numbers).

The result of time() does not change during the course of a command
execution.

EXAMPLES
write(ctime(time())+"n");

Print out the current date and time.

   See Also: 
      efun::ctime(), efun::gmtime(), efun::localtime(), efun::utime()