public class efun {
   /**
    * Low-level access to the command parser: take the \p command, parse it into verb and argument and call the appropriate action added to \p origin (read: \p origin is the object 'issuing' the command). For the execution of the function(s), `this_player()` is set to player. The function also sets results of `query_command()` and `query_verb()` to match the given \p command.
    * 
    * The result is non-0 if the command was found and execute, and 0 otherwise.
    * 
    * The efun raises a privilege violation ("execute_command", this_object(), origin, command).
    * 
    * Note that this function does not use the @ref driver_hook_modify_command "H_MODIFY_COMMAND" and @ref driver_hook_notify_fail "H_NOTIFY_FAIL" hooks; efun::notify_fail() is can be used, but must be evaluated by the caller.
    * 
    * @synopsis{
    * int execute_command(string command, object origin, object player)
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * }
    * 
    * @see @ref driver_hook_overview "hook", efun::match_command(), efun::command(), efun::notify_fail(), efun::command_stack()
   **/
   int execute_command(string command, object origin, object player);
}
