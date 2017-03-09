public class efun {
   /**
    * Take the command \p command, parse it, and return an array of all matching actions added to \p origin (read: \p origin is the object 'issuing' the command).
    * 
    * Each entry in the result array is itself an array of:
    * 
    * - string [`CMDM_VERB`]:   The matched verb.
    * - string [`CMDM_ARG`]:    The argument string remaining, or 0 if none.
    * - object [`CMDM_OBJECT`]: The object defining the action.
    * - string [`CMDM_FUN`]:    The name of the function to call in `CMDM_OBJECT`, which may be static.
    * 
    * The efun is useful for both debugging, and for implementing your own @ref driver_hook_command "H_COMMAND" handling.
    * 
    * @headerfile <commands.h>
    * 
    * @synopsis{
    * mixed * match_command(string command, object origin)
    * }
    * 
    * @history{
    * introduced (3.3.259)
    * }
    * 
    * @see @ref driver_hook_overview "hook", efun::execute_command(), efun::command(), efun::notify_fail(), efun::command_stack()
   **/
   mixed * match_command(string command, object origin);
}
