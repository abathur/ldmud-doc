clean_up {#driver_hook_clean_up}
================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_CLEAN_UP, value)
}

@param value int <closure>(int ref, object ob)
@param value void|int <name>(int ref)

Optional hook to clean up an object. Hook setting can be any closure, or the name of the function to call in the object.

This hook is called for an object if it hasn't been used for at least TIME_TO_CLEAN_UP seconds, to give it the opportunity to self destruct.

If the hook is a closure, it is called with the refcount of the object to clean up as first argument, and with the object itself as second. Lambda closures are also bound to the object prior to the call.

If the hook is the name of an lfun, it is called in the object with its refcount as argument.

In both calls, the refcount is constructed as:

~~~{.c}
ref = 0: the object is a clone, or a blueprint with
         replaced program.
ref = 1: the object is a swapped or unused blueprint.
ref > 1: the object is a used blueprint with `ref` references.

~~~
The cleanup method has the possibility to destruct the object. To survive this time, but try again some time later, the call has to result in a non-zero value.

If the hook specifies a non-existing lfun, or if the call returns 0, no further attempt to clean up this object will be made.

@see @ref driver_hook_overview "hook"
