erq_stop {#driver_hook_erq_stop}
================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_ERQ_STOP, value)
}

@param value void <closure>()

Optional hook to notify the mudlib about the termination of the erq demon. Hook setting may be any closure.

The closure is called without arguments and may do whatever it likes to clean-up after the erq.

@see @ref driver_hook_overview "hook"
