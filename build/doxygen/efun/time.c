public class efun {
   /**
    * Return number of seconds elapsed since `1. Jan 1970, 0.0:0 GMT`.
    * 
    * The time is based on the time provided by the host system, but the driver does make sure the result of efun::time() is monotonically increasing (ie. changes only to bigger numbers).
    * 
    * The result of efun::time() does not change during the course of a command execution.
    * 
    * @synopsis{
    * int time()
    * }
    * 
    * @usage{
    * Print out the current date and time:
    * 
    * ~~~{.c}
    * write(ctime(time())+"\n");
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::ctime(), efun::gmtime(), efun::localtime(), efun::utime()
   **/
   int time();
}
