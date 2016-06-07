public class master {
   /**
    * Check if the interactive user is allowed to use tracing.
    * 
    * The argument <what> denotes the action for which permission is to be
    * checked, <arg> is the argument given to the traceing efun:
    * 
    * +---------------+-------------------------------------------+
    * | <what>        | notes                                     |
    * +===============+===========================================+
    * | "trace"       | Is the user allowed to use tracing? <arg> |
    * |               | is the tracelevel argument given.         |
    * +---------------+-------------------------------------------+
    * | "traceprefix" | Is the user allowed to set a traceprefix? |
    * |               | <arg> is the prefix given.                |
    * +---------------+-------------------------------------------+
    * 
    * @synopsis{
    * int valid_trace(string what, int|string arg)
    * }
    * 
    * @see efun::trace(), @ref driver_concepts_memory "memory"
   **/
   int valid_trace(string what, int|string arg);
}
