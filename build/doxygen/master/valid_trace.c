public class master {
   /**
    * Check if the interactive user is allowed to use tracing.
    * 
    * The argument \p what denotes the action for which permission is to be checked, \p arg is the argument given to efun::trace().
    * 
    * | \p what       | notes                                                                            |
    * |---------------|----------------------------------------------------------------------------------|
    * | "trace"       | Is the user allowed to use tracing? \p arg is the tracelevel argument given.     |
    * | "traceprefix" | Is the user allowed to set a traceprefix? \p arg is the prefix given.            |
    * |               |                                                                                  |
    * 
    * @synopsis{
    * int valid_trace(string what, int|string arg)
    * }
    * 
    * @see efun::trace()
   **/
   int valid_trace(string what, int|string arg);
}
