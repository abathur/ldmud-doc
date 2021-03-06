public class efun {
   /**
    * Sets the trace flags and returns the old trace flags. When tracing is on, a lot of information is printed during execution and too much output can crash your connection or even the whole driver.
    * 
    * Tracing is done on a per-connection basis: each interactive(!) user may specifiy their own tracelevel and -prefix. Each gets the traceoutput for just the code executed during the evaluation of the commands he entered.
    * 
    * The trace bits are:
    * 
    * `TRACE_NOTHING`     (  0): stop tracing.
    * `TRACE_CALL`        (  1): trace all calls to lfuns.
    * `TRACE_CALL_OTHER`  (  2): trace call_others()s.
    * `TRACE_RETURN`      (  4): trace function returns.
    * `TRACE_ARGS`        (  8): print function arguments and results.
    * `TRACE_EXEC`        ( 16): trace all executed instructions.
    * `TRACE_HEART_BEAT`  ( 32): trace heartbeat code.
    * `TRACE_APPLY`       ( 64): trace driver applies.
    * `TRACE_OBJNAME`     (128): print the object names.
    * 
    * `TRACE_EXEC` and `TRACE_HEART_BEAT` should be avoided as they cause massive output! `TRACE_OBJNAME` should be avoided when you know what you trace.
    * 
    * master::valid_trace() is called with `("trace", traceflags)` as argument to verify the use of this efun.
    * 
    * @headerfile <trace.h>
    * 
    * @synopsis{
    * int trace(int traceflags)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * object obj;
    * string prefix;
    * obj = find_player("wessex");
    * prefix = object_name(obj);
    * prefix = prefix[1..];  // cut off the leading "/"
    * traceprefix(prefix);
    * // From here on, only code in the object "std/player#69"
    * // will be traced.
    * //
    * trace(TRACE_CALL|TRACE_CALL_OTHER|TRACE_RETURN|TRACE_ARGS);
    * ...
    * trace(TRACE_NOTHING);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- passes the traceflags argument to the valid_trace apply as well.
    * }
    * 
    * @see efun::traceprefix()
   **/
   int trace(int traceflags);
}
