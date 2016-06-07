public class efun {
   /**
    * Return the time since 1. Jan 1970, 00:00:00 GMT in microsecond
    * precision.
    * 
    * Return is an array:
    * int[0]: number of seconds elapsed
    * int[1]: number of microseconds within the current second.
    * 
    * @synopsis{
    * int * utime()
    * }
    * 
   **/
   int * utime();
}
EXAMPLES
   write(ctime(utime())+"n");

   Print out the current date and time.