.. efun:: void pg_close()
  :optional:

  Close the database connection for the current object, if there is one.

  The function is available only if the driver is compiled with
  PostgreSQL support. In that case, __PGSQL__ is defined.

  The efun triggers a privilege violation ("pgsql", "pg_close").

.. history
  :history 3.3.445 introduced:
  :history 3.3.640 changed: added the privilege violation.

  .. seealso:: :concept:`pgsql`, :efun:`pg_connect`, :efun:`pg_conv_string`, :efun:`pg_query`, :efun:`pg_pending`, :master:`privilege_violation`
