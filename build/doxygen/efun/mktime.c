public class efun {
   /**
    * If the argument \p ts is an array with 9 elements (int) according to the result of efun::localtime() or efun::gmtime(), this function returns the number of seconds passed since the epoch (`00:00:00 UTC, January 1, 1970`). This can be used to store a date or time as an integer value or to compute differences betweens two different dates or times.
    * 
    * The array \p ts has to have the following structure:
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
    * `TM_YDAY` and `TM_WDAY` are ignored and can contain arbitrary integer values.
    * 
    * @headerfile <time.h>
    * 
    * @synopsis{
    * int mktime(int *ts)
    * }
    * 
    * @usage{
    * A date and time (user input) shall be stored as unix timestamp. In the below example, `unixtime` holds the unix timestamp corresponding to "Wed Oct 24 10:48:00 2007":
    * 
    * ~~~{.c}
    * int unixtime = mktime( ({0, 48, 09, 24, 09, 2007, 0, 01, 0}) );
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.718)
    * }
    * 
    * @see efun::ctime(), efun::gmtime(), efun::localtime(), efun::time(), efun::utime()
   **/
   int mktime(int *ts);
}
