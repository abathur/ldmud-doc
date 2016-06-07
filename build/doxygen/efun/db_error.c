public class efun {
   /**
    * @synopsis{
    * string db_error(int handle)
    * }
    * 
   **/
   string db_error(int handle);
}
Return a string describing the error which occured during the last
database transaction. If the last database transaction was successful,
this call returns 0.

The function is available only if the driver is compiled with
mySQL support. In that case, __MYSQL__ is defined.

The efun triggers a privilege violation ("mysql", "db_error").

Added in 3.2.9 .
LDMud 3.2.11 added the privilege violation.

   See Also: 
      efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), @ref driver_concepts_mysql "mysql", master::privilege_violation()
