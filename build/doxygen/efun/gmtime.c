public class efun {
   /**
    * Interpret the argument clock as number of seconds since `Jan, 1st, 1970, 0:00`, and return the time in UTC in a nice structure. if \p clock is not specified, `time()` is used as default.
    * 
    * Alternatively, accept an array of two ints: the first is \p clock value as in the first form, the second int is the number of microseconds elapsed in the current second, which is ignored.
    * 
    * The result is an array of integers:
    * 
    * | place                     | contains                          |
    * |---------------------------|-----------------------------------|
    * | int `TM_SEC`   (0)        | Seconds (0..59)                   |
    * | int `TM_MIN`   (1)        | Minutes (0..59)                   |
    * | int `TM_HOUR`  (2)        | Hours (0..23)                     |
    * | int `TM_MDAY`  (3)        | Day of the month (1..31)          |
    * | int `TM_MON`   (4)        | Month of the year (0..11)         |
    * | int `TM_YEAR`  (5)        | Year (e.g. 2001)                  |
    * | int `TM_WDAY`  (6)        | Day of the week (Sunday = 0)      |
    * | int `TM_YDAY`  (7)        | Day of the year (0..365)          |
    * | int `TM_ISDST` (8)        | TRUE during daylight saving time  |
    * 
    * @headerfile <time.h>
    * 
    * @synopsis{
    * int * gmtime(int clock)
    * int * gmtime(int *uclock)
    * }
    * 
    * @usage{
    * The following trivial example prints the current day:
    * 
    * ~~~{.c}
    * printf("Today is %s\n",
    *      ({ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
    *         "Friday", "Saturday" })[gmtime()[TM_WDAY]]);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::ctime(), efun::localtime(), efun::time(), efun::utime()
   **/
   int * gmtime(int *uclock);
}
