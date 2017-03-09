public class efun {
   /**
    * Returns an array with all open handles to the SQL-server. As mySQL is most of the time limited to 100 connections, you should not let this number grow too big. The handles are sorted in a special order: The last used handle is the first one and the handle that hasn't been used for the longest time is the last one. If no handles are open, an empty array is returned.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_handles").
    * 
    * @synopsis{
    * int * db_handles()
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_error(), efun::db_exec(), efun::db_fetch(), efun::db_insert_id(), master::privilege_violation()
   **/
   int * db_handles();
}
