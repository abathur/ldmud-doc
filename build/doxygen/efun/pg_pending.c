public class efun {
   /**
    * @synopsis{
    * int pg_pending()
    * int pg_pending(object obj)
    * }
    * 
   **/
   int pg_pending(object obj);
}
Return the number of pending queries for the connection on the given
object <obj> (default is the current object). The object has no
database connection, return -1.

The function is available only if the driver is compiled with
PostgreSQL support. In that case, __PGSQL__ is defined.

The efun triggers a privilege violation ("pgsql", "pg_pending").

Added in 3.3.445.
LDMud 3.3.640 added the privilege violation.

      See Also: 
         @ref driver_concepts_pgsql "pgsql", efun::pg_connect(), efun::pg_conv_string(), efun::pg_query(), efun::pg_close(),

   master::privilege_violation()
