default_method {#driver_hook_default_method}
============================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_DEFAULT_METHOD, value)
}

@param value int <name>(mixed & result, string fun, varargs args)
@param value int <closure>(mixed & result, object ob, string fun, varargs args)

Optional hook to provide default implementation for unresolved calls. Hook setting can be any closure, or the name of the function to call in the object.

This hook is called whenever a efun::call_other(), efun::call_resolved() or efun::call_out() on named function (as opposed to a closure) couldn't be resolved. The hook has then the opportunity to provide a default implementation.

Exempt from this behaviour are calls to the master object, to simul-efuns, and calls done with efun::call_direct() and efun::call_direct_resolved().

If the hook is the name of an lfun, it is called in the target object; otherwise if it is a closure, the target object is passed as parameter <ob>.

The other parameters passed are the name <fun> of the called function, the arguments <args> passed to the call (if any), and a reference <result> to a variable for the call result.

If the hook can resolve the call, it has to return the call result in <result> and 1 as function result.

If the hook can not (or doesn't want to) resolve the call, it has to return 0.

@history{
introduced (3.3.113) -- allowed static functions to be given by name.
}

@see @ref driver_hook_overview "hook"
