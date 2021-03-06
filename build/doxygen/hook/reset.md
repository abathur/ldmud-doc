reset {#driver_hook_reset}
==========================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_RESET, value)
}

@param value void|int <closure> ( void )
@param value void <name>(1)

Optional hook to reset an object. Hook setting can be unbound lambda closures, or the name of the function (static or public) to call in the object.

If the hook is a closure, it is bound to the object to be reset and called with no argument.

If the result of this call is a positive number, it is used as the interval to wait before the next applied::reset(). If the result is 0, the default interval computed from TIME_TO_RESET is used. If the result is a negative number, the object will not be reset again, unless directed otherwise by efun::set_next_reset().

If the hook is defined as the name of an lfun in the object, it is called in the object with 1 as argument, and any result is ignored. In this call the efun::previous_object() is the object initiating the reset. If the function does not exist, the object won't be reset again.

@par note: an object is only reset by call to this hook if it has been used since the last reset.

@history{
changed (3.2.10) -- allowed static functions to be given by name.
}

@see @ref driver_hook_overview "hook"
