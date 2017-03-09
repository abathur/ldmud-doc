move_object {#driver_hook_move_object}
======================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_MOVE_OBJECT0, value)
set_driver_hook(H_MOVE_OBJECT1, value)
}

@param value void <closure>(object item, object dest)

Mandatory hooks to implement the efun void efun::move_object(). Hook setting must be an unbound lambda closure.

Upon call, the hook has to perform the move itself (by using efun::set_environment()) and all depending actions (like the calls to applied::init() to add actions).

The difference lies in the binding of the set hook prior to the call: the H_MOVE_OBJECT0 closure is bound to the current object, the H_MOVE_OBJECT1 to 'item'.

If both hooks are set, H_MOVE_OBJECT0 is ignored.

@see efun::move_object(), efun::set_environment(), @ref driver_hook_overview "hook"
