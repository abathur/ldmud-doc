public class efun {
   /**
    * @synopsis{
    * int execute_command(string command, object origin, object player)
    * }
    * 
   **/
   int execute_command(string command, object origin, object player);
}
Low-level access to the command parser: take the <command>, parse it
into verb and argument and call the appropriate action added to
<origin> (read: <origin> is the object 'issuing' the command).
For the execution of the function(s), this_player() is set to
player. The function also sets results of query_command() and
query_verb() to match the given <command>.

The result is non-0 if the command was found and execute, and 0
otherwise.

The efun raises a privilege violation ("execute_command",
this_object(), origin, command).

Note that this function does not use the H_MODIFY_COMMAND
and H_NOTIFY_FAIL hooks; the notify_fail() efun is can be used,
but must be evaluated by the caller.

Introduced in LDMud 3.2.7.

   See Also: 
      `hooks`, efun::match_command(), efun::command(), efun::notify_fail(), efun::command_stack()
