.. efun:: void debug_message(string text)
  void debug_message(string text, int flags)
  :include: <debug_message.h>

  Prints the given text to stdout, stderr, the <host>.debug.log file,
  or any combination of these.

  The parameter <flags> is a combination of bitflags determining the
  target and the mode of writing.

  The target flags are: DMSG_STDOUT, DMSG_STDERR and DMSG_LOGFILE.
  If the flag DMSG_STAMP is given, the message is prepended with the
  current date and time in the format 'YYYY.MM.DD HH:MM:SS '.

  If <flags> is given as 0, left out, or contains no target
  definition, debug_message() will print to stdout and to the logfile.

  .. usage::

    debug_message("This goes to stdout and the logfile.\n");
    debug_message("This goes to stderr.\n", DMSG_STDERR);
    debug_message("This goes to stdout and stderr.\n"
                 , DMSG_STDOUT | DMSG_STDERR);

    debug_message("This goes to stdout and the logfile, with timestamp.\n"
                 , DMSG_STAMP);
    debug_message("This goes to stdout and has the timestamp in front.\n"
                 , DMSG_STDOUT | DMSG_STAMP);

  :history 3.2.1@34 introduced:
  :history 3.2.9 changed: added the <flags> parameter

  .. seealso:: :efun:`last_instructions`
