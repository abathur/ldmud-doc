efuns {#driver_LPC_efuns}
=========================
Efuns are "system calls" in the LPC driver, the C program which compiles and executes the LPC programs of the mudlib. These are hardcoded functions which perform basic tasks which would be ineffective or impossible to be implemented in the mudlib.

There are efuns for accessing the underlying filesystem, for creating, moving and destructing objects, for writing messages to users, for manipulation of LPC data types.

@see @ref driver_efun_efun "efun", @ref driver_LPC_lfuns "lfuns", @ref driver_applied_applied "applied", @ref driver_master_master "master"
