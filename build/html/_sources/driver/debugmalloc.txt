.. command:: debugmalloc

  This command is hardcoded into the driver.

  Toggles the debug mode for the memory managment.
  If the O_IS_WIZARD flag is used in the mudlib (i.e. if
  set_is_wizard() was called), this command is allowed only for
  users that have this flag set.

  :history 3.2.7 changed: Deactivated by default, it was effectless before anyway.

  .. seealso:: :driver:`malloc`, :driver:`status`, :concept:`memory`, :concept:`objects`, :efun:`debug_info`, :efun:`set_is_wizard`
