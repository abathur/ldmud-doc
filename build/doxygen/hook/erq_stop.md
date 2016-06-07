erq_stop {#driver_hook_erq_stop}
================================
Optional hook to notify the mudlib about the termination of the erq demon. Hook setting may be any closure.

The closure is called without arguments and may do whatever it likes to clean-up after the erq.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_ERQ_STOP, value)
}

@see 
Arguments: 
- value (@ref driver_LPC_closures "closure") -- void <closure>()
