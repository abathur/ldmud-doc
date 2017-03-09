public class efun {
   /**
    * Return the number of pending queries for the connection on the given object \p obj (default is the current object). If the object has no database connection, return -1.
    * 
    * The function is available only if the driver is compiled with PostgreSQL support. In that case, @ref driver_topics_predefined "__PGSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("pgsql", "pg_pending").
    * 
    * @synopsis{
    * int pg_pending()
    * int pg_pending(object obj)
    * }
    * 
    * @history{
    * introduced (3.3.445)
    * changed (3.3.640) -- added the privilege violation.
    * }
    * 
    * @see efun::pg_connect(), efun::pg_conv_string(), efun::pg_query(), efun::pg_close(), master::privilege_violation()
   **/
   int pg_pending(object obj);
}
