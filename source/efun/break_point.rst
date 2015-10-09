.. efun:: void break_point()
  :optional:

  This function is for system internal use and should never be called by
  user objects. It is supposed to check the stack integrity and aborts
  the driver when it detects corruption.

  .. seealso:: :efun:`shutdown`, :efun:`swap`
