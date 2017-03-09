load_uids {#driver_hook_load_uids}
==================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_LOAD_UIDS, value)
}

@param value mixed <closure> (string objectname)

Mandatory hooks to determine the uid and euid of loaded or cloned objects. Hook settings can be any closure.

When an object is newly loaded, the @ref driver_hook_load_uids "H_LOAD_UIDS" hook is called with the object name as argument. The new object already exists, but has 0 uids.

For the result, the following possibilities exist (<num> is a non-zero number, <no-string> is anything but a string):

~~~{.c}
"<uid>"                    -> uid = "<uid>", euid = "<uid>"
({ "<uid>", "<euid>" })    -> uid = "<uid>", euid = "<euid>"
({ "<uid>", <no-string> }) -> uid = "<uid>", euid = 0

~~~
If strict-euids is not active, the following results are possible, too:

~~~{.c}
<num>                      -> uid = 0, euid = 0
({ <num>, "<euid>" })      -> uid = 0, euid = "<euid>"
({ <num>, <no-string> })   -> uid = 0, euid = 0

~~~

@see @ref driver_hook_overview "hook", @ref driver_hook_clone_uids "clone_uids"
