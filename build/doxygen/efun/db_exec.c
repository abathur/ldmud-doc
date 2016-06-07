public class efun {
   /**
    * @synopsis{
    * int db_exec(int handle, string statement)
    * }
    * 
   **/
   int db_exec(int handle, string statement);
}
Execute the SQL-statement <statement> for the connection <handle> to
the SQL-server. The result is the handle if all went okay. If there
was an error in the statement, 0 is returned.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_exec").

Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

   See Also: 
      efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), @ref driver_concepts_mysql "mysql", master::privilege_violation()
