dumpallobj {#driver_driver_dumpallobj}
======================================
Write a list of all loaded or cloned objects into the file
OBJ_DUMP, and a list of all destructed objects into the
file DEST_OBJ_DUMP. Both files are located in the root directory of
the mudlib.

@par warning:these files can be very large, and if the driver is low
on memory there is a certain crash probability.

If the O_IS_WIZARD flag is used in the mudlib (i.e. if
set_is_wizard() was called), this command is allowed only for
users that have this flag set.

For every live object, a line is written into the file with the
following information in the given order:

- object name
- size in memory, shared data counted only once
- size in memory if data wouldn't be shared
- number of references
- 'HB' if the object has a heartbeat, nothing if not.
- the name of the environment, or '--' if the object has no
environment
- in parentheses the number of execution ticks spent in this
object
- the swap status:
  - nothing if not swapped
  - 'PROG SWAPPED' if only the program is swapped
  - 'VAR SWAPPED' if only the variabes are swapped
  - 'SWAPPED' if both program and variables are swapped
  
- the time the object was created

For every destructed object, a line is written into the file with the
following information in the given order:

- object name
- number of references
- 'NEW' if the object was destructed in this execution
thread, nothing if it is older already.

@history{
changed (3.2.9) -- added the DEST_OBJ_DUMP.
changed (3.2.10) -- added the object creation time to OBJ_DUMP.
}

@see @ref driver_concepts_memory "memory", @ref driver_concepts_objects "objects", efun::debug_info(), efun::set_is_wizard()