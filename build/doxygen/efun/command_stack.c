public class efun {
   /**
    * Return an array describing the current command stack. The array has `command_stack_depth()` entries, the first describing the top-level command, and the last describing the current one.
    * 
    * Each entry is an array itself with these entries:
    * 
    * string [CMD_VERB]:    the verb of this command
    * string [CMD_TEXT]:    the full command text
    * object [CMD_ORIGIN]:  the original command giver
    * object [CMD_PLAYER]:  the current command giver
    * mixed  [CMD_FAIL]:    the notify_fail setting (or 0).
    * mixed  [CMD_FAILOBJ]: the object which set the notify_fail setting.
    * 
    * `CMD_ORIGIN` and `CMD_PLAYER` are usually the same; there is a difference only if @ref driver_hook_modify_command "H_MODIFY_COMMAND" changes the command giver with efun::set_this_player().
    * 
    * @par note: any of the entries may be returned as 0.
    * 
    * @headerfile <commands.h>
    * 
    * @synopsis{
    * mixed * command_stack(void)
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.2.8) -- added the CMD_FAILOBJ result
    * }
    * 
    * @see efun::command(), efun::command_stack_depth(), efun::notify_fail()
   **/
   mixed * command_stack(void);
}
