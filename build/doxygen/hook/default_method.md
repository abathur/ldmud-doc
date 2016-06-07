default_method {#driver_hook_default_method}
============================================
Optional hook to provide default implementation for unresolved calls. Hook setting can be any closure, or the name of the function to call in the object.

This hook is called whenever a call_other(), call_resolved() or call_out() on named function (as opposed to a closure) couldn't be resolved. The hook has then the opportunity to provide a default implementation.

Exempt from this behaviour are calls to the master object, to simul-efuns, and calls done with call_direct() and call_direct_resolved().

If the hook is the name of an lfun, it is called in the target object; otherwise if it is a closure, the target object is passed as parameter <ob>.

The other parameters passed are the name <fun> of the called function, the arguments <args> passed to the call (if any), and a reference <result> to a variable for the call result.

If the hook can resolve the call, it has to return the call result in <result> and 1 as function result.

If the hook can not (or doesn't want to) resolve the call, it has to return 0.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_DEFAULT_METHOD, value)
}

@history{
introduced (3.3.113) -- allowed static functions to be given by name.
}

@see 
Arguments: 
- value (@ref driver_LPC_string "string") -- int <name>(mixed & result, string fun, varargs args)
- value (@ref driver_LPC_closures "closure") -- int <closure>(mixed & result, object ob, string fun, varargs args)
