clone_uids {#driver_hook_clone_uids}
====================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_CLONE_UIDS, value)
}

@param value mixed <closure>(object blueprint, string objectname)

Mandatory hooks to determine the uid and euid of cloned objects. Hook settings can be any closure.

When an object is cloned, the @ref driver_hook_clone_uids "H_CLONE_UIDS" hook is called with the blueprint object as the first argument and the clone's designated name as the second. The new object already exists, but has 0 uids.

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

@see @ref driver_hook_overview "hook", @ref driver_hook_load_uids "load_uids"
