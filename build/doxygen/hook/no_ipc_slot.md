no_ipc_slot {#driver_hook_no_ipc_slot}
======================================
Optional hook specifying the message given to logins rejected due to space limitations (MAX_PLAYER). Hook setting has to be string.

If set to 0, the default message "Lpmud is full. Come back later." is issued.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_NO_IPC_SLOT, value)
}

@see 
Arguments: 
- value (@ref driver_LPC_int "int") -- 0
- value (@ref driver_LPC_string "string") -- <msg>
