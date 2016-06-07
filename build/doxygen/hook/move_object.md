move_object {#driver_hook_move_object}
======================================
Mandatory hooks to implement the efun void move_object(). Hook setting must be an unbound lambda closure.

Upon call, the hook has to perform the move itself (by using set_environment()) and all depending actions (like the calls to init() to add actions).

The difference lies in the binding of the set hook prior to the call: the H_MOVE_OBJECT0 closure is bound to the current object, the H_MOVE_OBJECT1 to 'item'.

If both hooks are set, H_MOVE_OBJECT0 is ignored.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_MOVE_OBJECT0, value)
set_driver_hook(H_MOVE_OBJECT1, value)
}

@see efun::move_object(), efun::set_environment()
Arguments: 
- value (@ref driver_LPC_closures "closure") -- void <closure>(object item, object dest)
