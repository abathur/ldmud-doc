public class efun {
   /**
    * Prints the given text to stdout, stderr, the `<host>.debug.log` file, or any combination of these.
    * 
    * The parameter \p flags is a combination of bitflags determining the target and the mode of writing.
    * 
    * The target flags are: `DMSG_STDOUT`, `DMSG_STDERR` and `DMSG_LOGFILE`. If the flag `DMSG_STAMP` is given, the message is prepended with the current date and time in the format `YYYY.MM.DD HH:MM:SS`.
    * 
    * If \p flags is given as 0, left out, or contains no target definition, efun::debug_message() will print to stdout and to the logfile.
    * 
    * @headerfile <debug_message.h>
    * 
    * @synopsis{
    * void debug_message(string text)
    * void debug_message(string text, int flags)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * debug_message("This goes to stdout and the logfile.\n");
    * debug_message("This goes to stderr.\n", DMSG_STDERR);
    * debug_message("This goes to stdout and stderr.\n"
    *              , DMSG_STDOUT | DMSG_STDERR);
    * 
    * debug_message("This goes to stdout and the logfile, with timestamp.\n"
    *              , DMSG_STAMP);
    * debug_message("This goes to stdout and has the timestamp in front.\n"
    *              , DMSG_STDOUT | DMSG_STAMP);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.1@34)
    * changed (3.2.9) -- added the flags parameter
    * }
    * 
    * @see efun::last_instructions()
   **/
   void debug_message(string text, int flags);
}
