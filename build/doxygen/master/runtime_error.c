public class master {
   /**
    * This function has to announce a runtime error to the active user. If the user has enough privileges, it might give him the full error message together with the source line. Else it should issue a decent message ("Your sensitive mind notices a wrongness in the fabric of space").
    * 
    * \p err is the error message, \p prg is the program executed (which might be an inherited program), \p curobj is the current object at the time of the error. \p line is the linenumber within the program.
    * 
    * If the error is a normal runtime error, \p culprit is -1. Otherwise, the error occured during a heartbeat and \p culprit is the object which applied::heart_beat() function was executed. Also, in case of a heartbeat error, the heartbeat for the \p culprit has been turned off.
    * 
    * If the error is caught on a higher level, \p caught is non-zero; otherwise it is 0.
    * 
    * Note that any of the the objects or programs might be destructed, ie. might be passed as 0.
    * 
    * @par warning: A common pitfall in implementing master::runtime_error() is that master::runtime_error() itself could run out of evaluation ticks, causing a runtime error itself. The workaround is to use efun::limited() like this:static void
    * handle_runtime_error ( string err, string prg, string curobj
    * , int line)
    * 
    * { ... the actual error handler ... }static void
    * call_runtime_error (string err, string prg, string curobj, int line)
    * {
    * limited(#'handle_runtime_error, ({ 200000 }), err, prg, curobj
    *    , line);
    *    
    * }void
    * runtime_error (string err, string prg, string curobj, int line)
    * {
    * limited(#'call_runtime_error, ({ LIMIT_UNLIMITED })
    *    , err, prg, curobj, line);
    *    
    * }
    * 
    * @synopsis{
    * void runtime_error(string err, string prg, string curobj, int line, mixed culprit, int caught)
    * }
    * 
    * @history{
    * changed (3.2.9) -- added the culprit argument.
    * changed (3.2.12/3.3.705) -- added the caught argument.
    * }
    * 
    * @see master::log_error(), master::heart_beat_error(), master::runtime_warning(), efun::raise_error(), efun::expand_define()
   **/
   void runtime_error(string err, string prg, string curobj, int line, mixed culprit, int caught);
}
