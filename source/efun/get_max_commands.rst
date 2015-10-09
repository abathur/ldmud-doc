.. efun:: int get_max_commands()
  int get_max_commands(object obj)

Return the max number of commands the interactive <obj> is
allowed to execute per second. A negative result means
'unlimited'.

If <obj> is not given, the current interactive is queried.
For non-interactive objects the result is 0.

A 'command' in this context means every received data packet
which causes a LPC call - actions and calls to input_to()
alike.

.. history
Introduced in LDMud 3.2.10.

  .. seealso:: :efun:`set_max_commands`
