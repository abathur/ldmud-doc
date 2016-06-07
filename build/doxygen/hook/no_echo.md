no_echo {#driver_hook_no_echo}
==============================
Optional hook to specifiy how to perform the telnet actions to switch the echo mode (used for e.g. password input_to()s). Hook setting may be any closure or a string. If not set, a default handling is performed.

If the setting is a string, it is used as name of an lfun to call in the interactive <user>, where <flag> is the echo-flag passed to the input_to() statement.

If the setting is a closure, it is called with the same arguments, and unbound lambda-closures being bound to this_player() prior to execution.

<local> is a boolean flag: it is TRUE when input_to() was called with the INPUT_NO_TELNET flag.

When set, the hook is called whenever the driver needs to change the echo mode, thus you can negotiate about things that are coupled with it, like LINEMODE or character-at-a-time.

@par warning:If this hook is used, the control of all telnet negotiation is transferred to the mudlib: all incoming negotiations are passed to H_TELNET_NEG, and the sending of no-echo negotiations is handled by this hook.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_NOECHO, value)
}

@history{
changed (3.2.11/3.3.593) -- added the <no_telnet> argument.
}

@see @ref driver_concepts_telnet "telnet", @ref driver_hook_telnet_neg "telnet_neg"
Arguments: 
- value (@ref driver_LPC_string "string") -- void <name>(int flag, object user, int no_telnet)
- value (@ref driver_LPC_closures "closure") -- void <closure>(int flag, object user, int no_telnet)
