notify_fail {#driver_hook_notify_fail}
======================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_NOTIFY_FAIL, value)
}

@param value <msg>
@param value string <closure>(string entered_command, object cmd_giver)

Mandatory hook to issue the default message if an entered command couldn't be parsed and no efun::notify_fail() command is in effect. Hook setting can be a any closure, or a string.

If set to a string, it is the message returned to the player.

If set to a closure, it is called with the command and the command giver as arguments, and the result is used as failure message. Lambda closures are bound to `this_player()` prior to execution.

<cmd_giver> is the object which received the command in the first place. It is usually identical with `this_player()`, unless the @ref driver_hook_modify_command "H_MODIFY_COMMAND" hook changed it.

@history{
changed (3.2.7) -- added the new 'command_giver' argument.
}

@see @ref driver_hook_overview "hook", @ref driver_hook_command "command", @ref driver_hook_modify_command "modify_command", @ref driver_hook_modify_command_fname "modify_command_fname", @ref driver_hook_send_notify_fail "send_notify_fail"
