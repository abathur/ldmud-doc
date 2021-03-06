.. efun:: string db_error(int handle)
  :optional:

  Return a string describing the error which occured during the last database transaction. If the last database transaction was successful, this call returns 0.

  The function is available only if the driver is compiled with mySQL support. In that case, :macro:`__MYSQL__` is defined.

  The efun triggers a privilege violation ("mysql", "db_error").

  :history 3.2.9 introduced:
  :history 3.2.11 changed: added the privilege violation.

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_coldefs`, :efun:`db_connect`, :efun:`db_exec`, :efun:`db_fetch`, :efun:`db_handles`, :efun:`db_insert_id`, :concept:`mysql`, :master:`privilege_violation`
