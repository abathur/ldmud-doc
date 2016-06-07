msg_discarded {#driver_hook_msg_discarded}
==========================================
Optional hook to specify a message or take other measures when a message had to be discarded, because they could not be delivered to the player <user>. If the hook is not set, a standard message is used.

If the hook is a string, this text will be sent as soon as possible to the player informing about the lost transmission.

If the hook is a closure, it is the function to be called and the result is used as the message to be sent. Lambda closures are bound to the interactive <user> first.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_MSG_DISCARDED, value)
}

@history{
3.3.719 (introduced)
}

@see efun::configure_interactive()
Arguments: 
- value (@ref driver_LPC_string "string") -- <msg>
- value (@ref driver_LPC_closures "closure") -- string <closure>(object user)
