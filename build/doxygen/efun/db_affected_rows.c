public class efun {
   /**
    * @synopsis{
    * int db_affected_rows(int handle)
    * }
    * 
   **/
   int db_affected_rows(int handle);
}
Return the number of affected rows of the last SQL-statement that
has been sent to the SQL-server via handle <handle>.
Only useful for DELETE- or UPDATE-operations.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_affected_rows").

Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

   See Also: 
      efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_insert_id(), efun::db_handles(), @ref driver_concepts_mysql "mysql", master::privilege_violation()
