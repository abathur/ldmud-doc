.. efun:: string db_error(int handle)
  :optional:

Return a string describing the error which occured during the last
database transaction. If the last database transaction was successful,
this call returns 0.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_error").

.. history
Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_coldefs`, :efun:`db_connect`, :efun:`db_exec`, :efun:`db_fetch`, :efun:`db_handles`, :efun:`db_insert_id`, :concept:`mysql`, :master:`privilege_violation`
