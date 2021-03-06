.. efun:: int * gmtime(int clock)
  int * gmtime(int *uclock)
  :include: <time.h>

  Interpret the argument clock as number of seconds since ``Jan, 1st, 1970, 0:00``, and return the time in UTC in a nice structure. if :arg:`clock` is not specified, ``time()`` is used as default.

  Alternatively, accept an array of two ints: the first is :arg:`clock` value as in the first form, the second int is the number of microseconds elapsed in the current second, which is ignored.

  The result is an array of integers:

  =========================  =================================
  place                      contains
  =========================  =================================
  int :macro:`TM_SEC`   (0)  Seconds (0..59)
  int :macro:`TM_MIN`   (1)  Minutes (0..59)
  int :macro:`TM_HOUR`  (2)  Hours (0..23)
  int :macro:`TM_MDAY`  (3)  Day of the month (1..31)
  int :macro:`TM_MON`   (4)  Month of the year (0..11)
  int :macro:`TM_YEAR`  (5)  Year (e.g. 2001)
  int :macro:`TM_WDAY`  (6)  Day of the week (Sunday = 0)
  int :macro:`TM_YDAY`  (7)  Day of the year (0..365)
  int :macro:`TM_ISDST` (8)  TRUE during daylight saving time
  =========================  =================================

  .. usage::

    The following trivial example prints the current day::

      printf("Today is %s\n",
           ({ "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
              "Friday", "Saturday" })[gmtime()[TM_WDAY]]);

  :history 3.2.9 introduced:

  .. seealso:: :efun:`ctime`, :efun:`localtime`, :efun:`time`, :efun:`utime`
