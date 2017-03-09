no_ipc_slot {#driver_hook_no_ipc_slot}
======================================
@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_NO_IPC_SLOT, value)
}

@param value 0
@param value <msg>

Optional hook specifying the message given to logins rejected due to space limitations (MAX_PLAYER). Hook setting has to be string.

If set to 0, the default message "Lpmud is full. Come back later." is issued.

@see @ref driver_hook_overview "hook"
