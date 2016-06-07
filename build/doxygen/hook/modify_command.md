modify_command {#driver_hook_modify_command}
============================================
Optional hook to modify commands (both entered or given by a call to command()) before the parser sees them (this includes special commands like 'status').

Hook setting can be any closure, the name of the function to call in the object, or a mapping.

For interactives this hook is used only if the interactive object has no command modifier already set by the efun set_modify_command().

If the hook is a closure, it is called with the entered command as first, and the command giving player as second argument. Lambda closures are bound to the command giving player, unbound-lambda closures remain unbound.

If the hook is a string, it is used as the name of an lfun in the command giving player, which is called with the command as argument.

If the hook is a mapping, it is queried with the given command as index, and the data retrieved is used as new command (defaults to 0 if no data is stored for a given command). If an entry is a closure instead of a string, it is called as:

~~~{.c}
int|string <closure>(string cmd, object player)

~~~
and the result from the call is used as 'the' command.

The result is treated equal in all three cases:

- If the result is a string, it is the new command to execute instead of the given one. Note that it is not possible to make several commands from one this way!
- If the result is a non-zero number, the given command is to be ignored. In case of the closure/lfun setting this may mean that the closure/lfun already executed it.
- If the result is 0, the originally given command is to be used.

It is possible for the hook to change the command giver (`this_player()`) for the execution of the command. This means that even though the commands are execute for the original commandgiver, this_player() will return the changed commandgiver.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_MODIFY_COMMAND, value)
}

@see @ref driver_hook_command "command", @ref driver_hook_modify_command_fname "modify_command_fname", @ref driver_hook_notify_fail "notify_fail", @ref driver_hook_send_notify_fail "send_notify_fail"
Arguments: 
- value (@ref driver_LPC_closures "closure") -- int|string <closure>(string cmd, object player)
- value (@ref driver_LPC_string "string") -- int|string <name>(string cmd)
- value (@ref driver_LPC_mappings "mapping") -- <mapping>