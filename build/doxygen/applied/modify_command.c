public class applied {
   /**
    * After efun::set_modify_command(mob)() was called for an interactive object iob, all commands for that user will be passed to `mob->modify_command(text)`, and the return will then be checked for actions. The actual name of the lfun to call is specified by the @ref driver_hook_modify_command_fname "H_MODIFY_COMMAND_FNAME" hook - traditionally it's `modify_command`.
    * 
    * If the result is a string, it is the new command to execute instead of the given one. Note that it is not possible to make several commands from one this way! If the result is a non-zero number, the given command is to be ignored. In case of the closure/lfun setting this may mean that the closure/lfun already executed it. If the result is 0, the originally given command is to be used.
    * 
    * @synopsis{
    * int|string modify_command(string cmd)
    * }
    * 
    * @history{
    * changed (3.2.1@109) -- the name of the lfun to call must be specified using H_MODIFY_COMMAND_FNAME.
    * }
    * 
    * @see efun::set_modify_command(), @ref driver_hook_overview "hook"
   **/
   int|string modify_command(string cmd);
}
