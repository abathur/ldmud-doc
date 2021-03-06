public class efun {
   /**
    * Return the number of affected rows of the last SQL-statement that has been sent to the SQL-server via handle \p handle. Only useful for DELETE- or UPDATE-operations.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_affected_rows").
    * 
    * @synopsis{
    * int db_affected_rows(int handle)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_insert_id(), efun::db_handles(), master::privilege_violation()
   **/
   int db_affected_rows(int handle);
}
