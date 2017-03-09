public class efun {
   /**
    * Execute the SQL-statement \p statement for the connection \p handle to the SQL-server. The result is the handle if all went okay. If there was an error in the statement, 0 is returned.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_exec").
    * 
    * @synopsis{
    * int db_exec(int handle, string statement)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), master::privilege_violation()
   **/
   int db_exec(int handle, string statement);
}
