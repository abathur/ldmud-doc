.. efun:: string db_conv_string(string str)
  :optional:

  Convert the string :arg:`str` into a string that is correctly interpretated for usage as a string in :efun:`db_exec`, e.g. ' is replaced with \' and so on.

  The function is available only if the driver is compiled with mySQL support. In that case, :macro:`__MYSQL__` is defined.

  :history 3.2.9 introduced:

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_close`, :efun:`db_coldefs`, :efun:`db_connect`, :efun:`db_exec`, :efun:`db_error`, :efun:`db_fetch`, :efun:`db_handles`, :efun:`db_insert_id`, :concept:`mysql`
