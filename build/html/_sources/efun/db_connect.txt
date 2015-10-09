.. efun:: int db_connect(string database)
  int db_connect(string database, string user)
  int db_connect(string database, string user, string password)
  :optional:

Connect to the database <database> on the local mySQL-server.
The return-value is the handle for this connection. Automatic
reconnects are enabled for this connection; see :concept:`mysql` for
implications.
If the database does not exist or the server is NOT started,
a runtime-error is raised.

If specified, the connection is made for <user> with <password>.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_connect").

.. history
Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

  .. seealso:: :efun:`db_affected_rows`, :efun:`db_conv_string`, :efun:`db_close`, :efun:`db_coldefs`,
 :efun:`db_exec`, :efun:`db_error`, :efun:`db_fetch`, :efun:`db_handles`,
 :efun:`db_insert_id`, :concept:`mysql`, :master:`privilege_violation`
