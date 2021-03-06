send_notify_fail {#driver_hook_send_notify_fail}
================================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_SEND_NOTIFY_FAIL, value)
}

@param value void <name>(string msg, object msgobj, object orig_cmd_giver)
@param value void <closure>(string msg, object msgobj, object orig_cmd_giver)

Optional hook to send the notify fail message, regardless of how it was determined, to the player. If the hook is not set, the message is delivered using efun::tell_object() internally. Hook setting can be a string or a closure.

If the hook is a string, it is the name of a (possibly static) function to call in the current command giver. If the hook is a closure, it is the function to be called. Lambda closures are bound to the current command giver first.

The arguments to the call are:
- <msg> is the notify fail message to be delivered.
- <msgobj> is the object which set the message. It is 0 for the default message.
- <orig_cmd_giver> is the object for which the original command was first received. It is usually identical with the current command giver `this_player()`.

@see @ref driver_hook_overview "hook", @ref driver_hook_command "command", @ref driver_hook_modify_command "modify_command", @ref driver_hook_modify_command_fname "modify_command_fname", @ref driver_hook_notify_fail "notify_fail"
