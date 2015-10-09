.. efun:: int pg_query (string query)
  int pg_query (string query, int flags)
  :include: <pgsql.h>
  :optional:

  Queue a new query <query> to the database connection on the current
  object. Return the unique id of the query. The query result itself
  will be passed as argument to the callback function.

  <flags> can be one of these values:
    PG_RESULT_ARRAY: Pass the query result as array.
    PG_RESULT_MAP:   Pass the query result as mapping.

  The function is available only if the driver is compiled with
  PostgreSQL support. In that case, __PGSQL__ is defined.

  The efun triggers a privilege violation ("pgsql", "pg_query").

.. history
  Added in 3.3.445.
  LDMud 3.3.640 added the privilege violation.

  .. seealso:: :concept:`pgsql`, :efun:`pg_connect`, :efun:`pg_conv_string`, :efun:`pg_pending`, :efun:`pg_close`, :master:`privilege_violation`
