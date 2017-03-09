public class efun {
   /**
    * Return a string describing the error which occured during the last database transaction. If the last database transaction was successful, this call returns 0.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_error").
    * 
    * @synopsis{
    * string db_error(int handle)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- added the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), master::privilege_violation()
   **/
   string db_error(int handle);
}
