.. command:: showsmallnewmalloced

  This command is hardcoded into the driver.

  Shows a list of recently allocated small memory blocks.
  If the O_IS_WIZARD flag is used in the mudlib (i.e. if
  set_is_wizard() was called), this command is allowed only for
  users that have this flag set.

  :history 3.2.7 changed: Deactivated by default.

  .. seealso:: :driver:`malloc`, :driver:`status`, :concept:`memory`, :concept:`objects`, :efun:`debug_info`, :efun:`set_is_wizard`
