.. efun:: string pg_conv_string(string str)
  :optional:

Convert the string <str> into a string that is correctly interpretated
for usage as a string in pg_query(), e.g. ' is replaced with \' and so
on.

The function is available only if the driver is compiled with
PostgreSQL support. In that case, __PGSQL__ is defined.

The efun triggers a privilege violation ("pgsql", "pg_connect").

.. history
Added in 3.3.708.

  .. seealso:: :concept:`pgsql`, :efun:`pg_query`, :efun:`pg_pending`, :efun:`pg_conv_string`, :efun:`pg_close`, :master:`privilege_violation`
