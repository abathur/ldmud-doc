.. efun:: mixed db_fetch(int handle)
  :optional:

Retrieve _ONE_ line of result of the latest SQL-action to the server
based on the handle <handle>. If not more results are on the server,
0 is returned.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_fetch").

.. history
Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_coldefs`, :efun:`db_connect`, :efun:`db_error`, :efun:`db_exec`, :efun:`db_handles`, :efun:`db_insert_id`, :concept:`mysql`, :master:`privilege_violation`
