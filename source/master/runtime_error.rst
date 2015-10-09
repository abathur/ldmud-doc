.. master:: void runtime_error( string err, string prg, string curobj, int line, mixed culprit, int caught)

  This function has to announce a runtime error to the active
  user. If the user has enough privileges, it might give him the
  full error message together with the source line. Else it
  should issue a decent message ("Your sensitive mind notices a
  wrongness in the fabric of space").

  <err> is the error message, <prg> is the program executed (which
  might be an inherited program), <curobj> is the current object at
  the time of the error. <line> is the linenumber within the program.

  If the error is a normal runtime error, <culprit> is -1. Otherwise,
  the error occured during a heartbeat and <culprit> is the object which
  heart_beat() function was executed. Also, in case of a heartbeat error,
  the heartbeat for the <culprit> has been turned off.

  If the error is caught on a higher level, <caught> is non-zero;
  otherwise it is 0.

  Note that any of the the objects or programs might be destructed, ie.
  might be passed as 0.

  One common pitfall in the implementation of runtime_error() is
  that runtime_error() itself could run out of evaluation ticks,
  causing a runtime error itself. The workaround is to use
  limited() like this::

    static void
    handle_runtime_error ( string err, string prg, string curobj
                         , int line)
    { ... the actual error handler ... }

    static void
    call_runtime_error (string err, string prg, string curobj, int line)
    {
        limited(#'handle_runtime_error, ({ 200000 }), err, prg, curobj
               , line);
    }

    void
    runtime_error (string err, string prg, string curobj, int line)
    {
        limited(#'call_runtime_error, ({ LIMIT_UNLIMITED })
               , err, prg, curobj, line);
    }

.. history
  :history 3.2.9 changed: added the <culprit> argument.
  :history 3.2.12/3.3.705 changed: added the <caught> argument.

  .. seealso:: :master:`log_error`, :master:`heart_beat_error`, :master:`runtime_warning`, :efun:`raise_error`, :efun:`expand_define`