public class efun {
   /**
    * Close the server-connection with the handle \p handle Return the handle-number on success.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_close").
    * 
    * @synopsis{
    * int db_close(int handle)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), master::privilege_violation()
   **/
   int db_close(int handle);
}
