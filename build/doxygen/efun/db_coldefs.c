public class efun {
   /**
    * Return an array with the column names of the current table. If the database didn't return a result, the result of this efun is 0.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_coldefs").
    * 
    * @synopsis{
    * string * db_coldefs(int handle)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_connect(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id(), master::privilege_violation()
   **/
   string * db_coldefs(int handle);
}
