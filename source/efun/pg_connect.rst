.. efun:: int pg_connect(string conn, string fun)
  int pg_connect(string conn, string fun, string|object obj, mixed extra, ...)
  int pg_connect(string conn, closure cl, mixed extra, ...)
  :optional:

  Open a database connection as directed by :arg:`conn`, and assign the callback function :arg:`fun`/:arg:`cl` with the optional :arg:`extra` parameters to it.

  The object holding the callback function becomes the controlling object; obiously it is an error to assign more than one connection to the same controlling object.

  The :arg:`conn` string is in the format accepted by Postgres' ``PQconnectStart()`` API functions. Pass an empty string to use the default options, or a string holding the ``'<key>=<value>'`` options separated by whitespace.

  .. todo:: could above link to pg docs?

  The most useful options are:

  dbname
    The database name

  user
    The user name to connect as.

  password
    Password to be used.

  Return 0 on success, and -1 on failure.

  The function is available only if the driver is compiled with PostgreSQL support. In that case, :macro:`__PGSQL__` is defined.

  The efun triggers a privilege violation ("pgsql", "pg_connect").

  .. todo:: privilege above

  :history 3.3.445 introduced:
  :history 3.3.640 changed: added the privilege violation.

  .. seealso:: :concept:`pgsql`, :efun:`pg_query`, :efun:`pg_pending`, :efun:`pg_conv_string`, :efun:`pg_close`, :master:`privilege_violation`
