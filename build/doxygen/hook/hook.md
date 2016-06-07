hook {#driver_hook_hook}
========================
To allow a greater flexibility of the muds, the gamedrivers since 3.2.1 moved several once hardcoded 'underground' activities from the driver into the mudlib. This includes for example the differences between compat and native mode.

The hooks are set with the privileged efun set_driver_hook(). Some of the hooks are mandatory, some not. Most hooks accept unbound lambda closures as values, some also lfun closures or even strings.

The hooks are identified by an ordinal number, for which symbolic names are defined in `/sys/driverhooks.h`.

@ref driver_hook_move_object "H_MOVE_OBJECT0"
@ref driver_hook_move_object "H_MOVE_OBJECT1"
Mandatory hooks to implement the efun void move_object().

@ref driver_hook_load_uids "H_LOAD_UIDS"
@ref driver_hook_clone_uids "H_CLONE_UIDS"
Mandatory hooks to determine the uid and euid of loaded or cloned objects.

@ref driver_hook_create_super "H_CREATE_SUPER"
@ref driver_hook_create_ob "H_CREATE_OB"
@ref driver_hook_create_clone "H_CREATE_CLONE"
Optional hooks to initialize an object after creation.

@ref driver_hook_create_super "H_CREATE_SUPER" is called for blueprints implicitely loaded by inheritance, @ref driver_hook_create_ob "H_CREATE_OB" for explicitely loaded blueprints/objects, and @ref driver_hook_create_clone "H_CREATE_CLONE" for cloned objects.

@ref driver_hook_reset "H_RESET"
Optional hook to reset an object.

@ref driver_hook_clean_up "H_CLEAN_UP"
Optional hook to clean up an object.

@ref driver_hook_default_method "H_DEFAULT_METHOD"
Optional hook to provide default implementation for unresolved calls.

@ref driver_hook_default_prompt "H_DEFAULT_PROMPT"
Optional hook for the command prompt. If this hook is not used, the driver will use "> " as the command prompt.

@ref driver_hook_print_prompt "H_PRINT_PROMPT"
Optional hook to print the current command prompt. If this hook is not set, the driver will just print the prompt to the user.

@ref driver_hook_command "H_COMMAND"
Optional hook to parse and execute commands. If this hook is used, it bypasses the normal command parsing done by the driver (including the MODIFY_COMMAND and NOTIFY_FAIL hooks).

@ref driver_hook_modify_command "H_MODIFY_COMMAND"
Optional hook to modify commands (both entered or given by a call to command()) before the parser sees them (this includes special commands like 'status').

@ref driver_hook_modify_command_fname "H_MODIFY_COMMAND_FNAME"
Mandatory hook specifying the name of the 'modify_command' lfun to call for newly entered commands as result of a set_modify_command().

@ref driver_hook_notify_fail "H_NOTIFY_FAIL"
Mandatory hook to issue the default message if an entered command couldn't be parsed and no notify_fail() command is in effect.

@ref driver_hook_send_notify_fail "H_SEND_NOTIFY_FAIL"
Optional hook to send the notify fail message, regardless of how it was determined, to the player. If the hook is not set, the message is delivered using tell_object() internally.

@ref driver_hook_no_ipc_slot "H_NO_IPC_SLOT"
Optional hook specifying the message given to logins rejected due to space limitations (MAX_PLAYER).

@ref driver_hook_include_dirs "H_INCLUDE_DIRS"
Semi-mandatory hook specifying the directories where <>-type include files are searched (this includes ""-includes not found as specified).

@ref driver_hook_auto_include "H_AUTO_INCLUDE"
Optional hook specifying a string to be included before the source of every compiled LPC object.

@ref driver_hook_telnet_neg "H_TELNET_NEG"
Optional hook to specifiy how to perform a single telnet negotiation. If not set, most telnet options are rejected (read: only a very minimal negotiation takes place).

@ref driver_hook_no_echo "H_NOECHO"
Optional hook to specifiy how to perform the telnet actions to switch the echo mode (used for e.g. password input_to()s). If not set, a default handling is performed.

IMPORTANT: If this hook is used, the control of all telnet negotiation is transferred to the mudlib (you must combine it with @ref driver_hook_telnet_neg "H_TELNET_NEG" to conform to the telnet protocol).

@ref driver_hook_erq_stop "H_ERQ_STOP"
Optional hook to notify the mudlib about the termination of the erq demon.

@ref driver_hook_msg_discarded "H_MSG_DISCARDED"
Optional hook to specify a message or take other measures when a message had to be discarded.

- hook::H_AUTO_INCLUDE()
- hook::H_CLEAN_UP()
- hook::H_CLONE_UIDS()
- hook::H_COMMAND()
- hook::H_CREATE_CLONE()
- hook::H_CREATE_OB()
- hook::H_CREATE_SUPER()
- hook::H_DEFAULT_METHOD()
- hook::H_DEFAULT_PROMPT()
- hook::H_ERQ_STOP()
- hook::H_INCLUDE_DIRS()
- hook::H_LOAD_UIDS()
- hook::H_MODIFY_COMMAND()
- hook::H_MODIFY_COMMAND_FNAME()
- hook::H_MOVE_OBJECT0()
- hook::H_MSG_DISCARDED()
- hook::H_NOECHO()
- hook::H_NO_IPC_SLOT()
- hook::H_NOTIFY_FAIL()
- hook::H_PRINT_PROMPT()
- hook::H_REGEXP_PACKAGE()
- hook::H_RESET()
- hook::H_SEND_NOTIFY_FAIL()
- hook::H_TELNET_NEG()

@history{
introduced (3.2.1) -- the hooks concept
changed (3.2.1@1) -- added H_MOVE_OBJECT0 and H_MOVE_OBJECT1
changed (3.2.1@34) -- added H_CLEAN_UP
changed (3.2.1@51) -- added H_MODIFY_COMMAND
changed (3.2.1@109) -- added H_MODIFY_COMMAND_FNAME
changed (3.2.1@55) -- added H_NOTIFY_FAIL and H_NO_IPC_SLOT
changed (3.2.1@57) -- added H_INCLUDE_DIRS
changed (3.2.1@60) -- added H_TELNET_NEG
changed (3.2.1@85) -- added H_NOECHO and H_ERQ_STOP
changed (3.2.7) -- added H_COMMAND
changed (3.2.9) -- added H_SEND_NOTIFY_FAIL and H_AUTO_INCLUDE
changed (3.3.113) -- added H_DEFAULT_METHOD
changed (3.3.163) -- added H_DEFAULT_PROMPT and H_PRINT_PROMPT
}

@see @ref driver_concepts_native "native", efun::set_driver_hook(), @ref driver_hook_move_object "move_object", @ref driver_applied_applied "applied", @ref driver_concepts_concepts "concepts", @ref driver_driver_driver "driver", @ref driver_efun_efun "efun", @ref driver_internals_internals "internals", @ref driver_LPC_lpc "LPC", @ref driver_master_master "master", @ref driver_obsolete_obsolete "obsolete"
