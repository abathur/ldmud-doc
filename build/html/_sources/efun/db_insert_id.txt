.. efun:: int db_insert_id(int handle)
  :optional:

After inserting a line into a table with an AUTO_INCREMENT field,
this efun can be used to return the (new) value of the AUTO_INCREMENT
field.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_insert_id").

.. history
Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_coldefs`, :efun:`db_connect`, :efun:`db_error`, :efun:`db_exec`, :efun:`db_fetch`, :efun:`db_handles`, :concept:`mysql`, :master:`privilege_violation`
