.. efun:: int enable_telnet(int num)
  int enable_telnet(int num, object obj)

  Enable or disable the telnet machine for the interactive object <obj>.
  Return the previous state of the telnet machine as result.

  <num> > 0 : enable telnet machine (default)
        = 0 : disable telnet machine
        < 0 : just query the current state of the telnet machine.
  <obj> : the interactive object, default is the current interactive.
          For non-interactive objects the function raises an error.

  The function raises a privilege_violation ("enable_telnet", obj, num)
  if <num> is >= 0. If the privilege is denied, the call is ignored.

  .. warning:: Careless use of this efun can cause great confusion for both driver and clients! The efun exists mainly to support PSYCmuve, and may vanish if a more consistent way of handling network connections is introduced.

.. history
  :history 3.2.10 introduced:

  .. seealso:: :master:`privilege_violation`, :efun:`input_to`
