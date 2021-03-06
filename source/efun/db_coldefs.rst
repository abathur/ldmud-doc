.. efun:: string * db_coldefs(int handle)
  :optional:

  Return an array with the column names of the current table. If the database didn't return a result, the result of this efun is 0.

  The function is available only if the driver is compiled with mySQL support. In that case, :macro:`__MYSQL__` is defined.

  The efun triggers a privilege violation ("mysql", "db_coldefs").

  :history 3.2.9 introduced:
  :history 3.2.11 changed: adds the privilege violation.

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_connect`, :efun:`db_exec`, :efun:`db_error`, :efun:`db_fetch`, :efun:`db_handles`, :efun:`db_insert_id`, :concept:`mysql`, :master:`privilege_violation`
