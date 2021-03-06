command {#driver_hook_command}
==============================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_COMMAND, value)
}

@param value int <closure>(string command, object command_giver)
@param value int <name>(string command, object command_giver)

Optional hook to parse and execute commands. If this hook is used, it bypasses the normal command parsing done by the driver (including the MODIFY_COMMAND and NOTIFY_FAIL hooks).

The hook is called with two parameters: the command received from the living (interactive user or NPC), and the living object (the 'command giver') itself. The hook has to return non-0 if the command was found and executed, and 0 otherwise.

At the time the hook is called, efun::query_command() returns the command string and efun::this_player() returns the living object. efun::query_verb() and efun::query_notify_fail() return 0.

If the hook is a string, it is the name of an lfun in the command giver; if the hook is a lambda closure, it is bound to the command giver before the call.

@see @ref driver_hook_overview "hook", @ref driver_hook_modify_command "modify_command", @ref driver_hook_modify_command_fname "modify_command_fname", @ref driver_hook_notify_fail "notify_fail", @ref driver_hook_send_notify_fail "send_notify_fail"
