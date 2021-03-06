.. efun:: int pg_pending()
  int pg_pending(object obj)
  :optional:

  Return the number of pending queries for the connection on the given object :arg:`obj` (default is the current object). If the object has no database connection, return -1.

  The function is available only if the driver is compiled with PostgreSQL support. In that case, :macro:`__PGSQL__` is defined.

  The efun triggers a privilege violation ("pgsql", "pg_pending").

  .. todo:: privilege violation

  :history 3.3.445 introduced:
  :history 3.3.640 changed: added the privilege violation.

  .. seealso:: :concept:`pgsql`, :efun:`pg_connect`, :efun:`pg_conv_string`, :efun:`pg_query`, :efun:`pg_close`, :master:`privilege_violation`
