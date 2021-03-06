create_clone {#driver_hook_create_clone}
========================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_CREATE_CLONE, value)
}

@param value void <name> (0)
@param value int <closure> ( void )
@param value int <closure> (object obj_to_init)

Optional hooks to initialize a cloned object after creation. Hook setting can be unbound lambda closures, or the name of the function (static or public) to call in the object.

If the hook is a closure expecting an argument, it is bound to the current object and called with the created object as argument. If the hook is a closure without arguments, it is bound to the object to be initalized and called.

If the result of the closure call is a non-zero number, it is used as the interval to wait before the first applied::reset(), else the default interval computed from TIME_TO_RESET is used.

If the hook is defined as the name of an lfun in the object, it is called in the object with 0 as argument, and any result is ignored.

@history{
changed (3.2.10) -- allowed static functions to be given by name.
}

@see @ref driver_hook_overview "hook", @ref driver_hook_create_ob "create_ob", @ref driver_hook_create_super "create_super"
