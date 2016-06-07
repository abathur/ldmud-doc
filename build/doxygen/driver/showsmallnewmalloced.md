showsmallnewmalloced {#driver_driver_showsmallnewmalloced}
==========================================================
This command is hardcoded into the driver.

Shows a list of recently allocated small memory blocks.
If the O_IS_WIZARD flag is used in the mudlib (i.e. if
set_is_wizard() was called), this command is allowed only for
users that have this flag set.

@history{
changed (3.2.7) -- Deactivated by default.
}

@see @ref driver_concepts_memory "memory", @ref driver_concepts_objects "objects", efun::debug_info(), efun::set_is_wizard()
