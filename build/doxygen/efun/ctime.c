public class efun {
   /**
    * @synopsis{
    * string ctime(int clock)
    * string ctime(int *uclock)
    * }
    * 
   **/
   string ctime(int *uclock);
}
Interpret the argument clock as number of seconds since Jan,
1st, 1970, 0.00 and convert it to a nice date and time string.
If clock is not specified, time() is used as default.

The second form is like the first, except that it takes as argument
an array of ints as it is returned from utime(): int[0] is the number
of seconds like before, int[1] is the number of microseconds within
that second.

EXAMPLES
write(ctime()+"n");

This will print out something like "Fri Jul 17 19:13:33 1992".

LDMud 3.2.9 introduced the second form.

   See Also: 
      efun::gmtime(), efun::localtime(), efun::mktime(), efun::strftime(), efun::time(), efun::utime()
