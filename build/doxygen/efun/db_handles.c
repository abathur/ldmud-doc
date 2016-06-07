public class efun {
   /**
    * @synopsis{
    * int * db_handles()
    * }
    * 
   **/
   int * db_handles();
}
Returns an array with all open handles to the SQL-server.
As mySQL is most of the time limited to 100 connections, you
should not let this number grow too big. The handles are sorted
in a special order: The last used handle is the first one and
the handle that hasn't been used for the longest time is
the last one. If no handles are open, an empty array is returned.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_handles").

Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

   See Also: 
      efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_error(), efun::db_exec(), efun::db_fetch(), efun::db_insert_id(), @ref driver_concepts_mysql "mysql", master::privilege_violation()
