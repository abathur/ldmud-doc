public class efun {
   /**
    * If called with a string, only objects matching this prefix will be traced. The string must not contain a leading "/" because the object names are stored internally without it. If called with a number, the traceprefix will be ignored and all objects will be traced. Returns the last traceprefix or 0 if there wasn't any.
    * 
    * master::valid_trace() is called with `("traceprefix", prefix)` as arguments to verify the use of this efun.
    * 
    * @headerfile <trace.h>
    * 
    * @synopsis{
    * string traceprefix(string prefix)
    * string traceprefix(int dummy)
    * }
    * 
    * @usage{
    * The following example shows the basics of how to set up (and later remove) a trace:
    * 
    * ~~~{.c}
    * object obj;
    * string prefix;
    * obj = find_player("wessex");
    * prefix = object_name(obj);
    * prefix = prefix[1..]; // cut off the leading "/"
    * traceprefix(prefix);
    *   // From here on, only code in the object "std/player#69"
    *   // will be traced.
    *   //
    * trace(TRACE_CALL | TRACE_CALL_OTHER | TRACE_RETURN | TRACE_ARGS);
    * ...
    * trace(TRACE_NOTHING);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- passes prefix to the valid_trace apply as well.
    * }
    * 
    * @see efun::trace()
   **/
   string traceprefix(int dummy);
}
