public class efun {
   /**
    * @synopsis{
    * int db_close(int handle)
    * }
    * 
   **/
   int db_close(int handle);
}
Close the server-connection with the handle <handle>
Return the handle-number on success.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_close").

Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

   See Also: 
      efun::db_affected_rows(), efun::db_conv_string(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), @ref driver_concepts_mysql "mysql", master::privilege_violation()
