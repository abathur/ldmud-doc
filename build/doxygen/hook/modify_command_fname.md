modify_command_fname {#driver_hook_modify_command_fname}
========================================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_MODIFY_COMMAND_FNAME, value)
}

@param value )

Mandatory hook specifying the name of the 'modify_command' lfun to call for newly entered commands as result of a efun::set_modify_command().

Hook setting must be a string.

If efun::set_modify_command() is used for an interactive user, all newly entered commands are first passed to the function named by this hook.

The function is called with the command as argument.

If the result is a string, it is the new command to execute instead of the given one. Note that it is not possible to make several commands from one this way!

If the result is a non-zero number, the given command is to be ignored. In case of the closure/lfun setting this may mean that the closure/lfun already executed it.

If the result is 0, the originally given command is to be used.

It is possible for the hook to change the command giver (efun::this_player()) for the execution of the command. This means that even though the commands are execute for the original commandgiver, efun::this_player() will return the changed commandgiver.

@see @ref driver_hook_overview "hook", @ref driver_hook_command "command", @ref driver_hook_modify_command "modify_command", @ref driver_hook_notify_fail "notify_fail", @ref driver_hook_send_notify_fail "send_notify_fail"
