opcdump {#driver_driver_opcdump}
================================
If the driver was compiled to do opcode profiling, this command
will save the collected profiling information into the file /OPC_DUMP.
If the O_IS_WIZARD flag is used in the mudlib (i.e. if
set_is_wizard() was called), this command is allowed only for
users that have this flag set.

@see @ref driver_concepts_memory "memory", @ref driver_concepts_objects "objects", efun::debug_info(), efun::set_is_wizard()
