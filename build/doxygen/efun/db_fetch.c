public class efun {
   /**
    * Retrieve _ONE_ line of result of the latest SQL-action to the server based on the handle \p handle. If not more results are on the server, 0 is returned.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_fetch").
    * 
    * @synopsis{
    * mixed db_fetch(int handle)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_error(), efun::db_exec(), efun::db_handles(), efun::db_insert_id(), master::privilege_violation()
   **/
   mixed db_fetch(int handle);
}
