public class efun {
   /**
    * Open a database connection as directed by \p conn, and assign the callback function \p fun/\p cl with the optional \p extra parameters to it.
    * 
    * The object holding the callback function becomes the controlling object; obiously it is an error to assign more than one connection to the same controlling object.
    * 
    * The \p conn string is in the format accepted by Postgres' `PQconnectStart()` API functions. Pass an empty string to use the default options, or a string holding the `'<key>=<value>'` options separated by whitespace.
    * 
    * The most useful options are:
    * 
    * dbname
    * The database name
    * 
    * user
    * The user name to connect as.
    * 
    * password
    * Password to be used.
    * 
    * Return 0 on success, and -1 on failure.
    * 
    * The function is available only if the driver is compiled with PostgreSQL support. In that case, @ref driver_topics_predefined "__PGSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("pgsql", "pg_connect").
    * 
    * @synopsis{
    * int pg_connect(string conn, string fun)
    * int pg_connect(string conn, string fun, string|object obj, mixed extra, ...)
    * int pg_connect(string conn, closure cl, mixed extra, ...)
    * }
    * 
    * @history{
    * introduced (3.3.445)
    * changed (3.3.640) -- added the privilege violation.
    * }
    * 
    * @see efun::pg_query(), efun::pg_pending(), efun::pg_conv_string(), efun::pg_close(), master::privilege_violation()
   **/
   int pg_connect(string conn, closure cl, mixed extra, ...);
}
