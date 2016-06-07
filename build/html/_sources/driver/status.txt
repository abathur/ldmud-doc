.. command:: status
  status tables
  status swap
  status malloc

  This command is hardcoded into the driver's input routine. It displays information about the run status of the system. If the O_IS_WIZARD flag is used in the mudlib (i.e. if set_is_wizard() was called), this command is allowed only for users that have this flag set.

  :history 3.2.7 changed: added the 'status malloc' variant.

  .. seealso:: :driver:`malloc`, :concept:`memory`, :concept:`objects`, :efun:`debug_info`, :efun:`set_is_wizard`
