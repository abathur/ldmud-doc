public class efun {
   /**
    * After inserting a line into a table with an `AUTO_INCREMENT` field, this efun can be used to return the (new) value of the `AUTO_INCREMENT` field.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("mysql", "db_insert_id").
    * 
    * @synopsis{
    * int db_insert_id(int handle)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * changed (3.2.11) -- adds the privilege violation.
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_conv_string(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_error(), efun::db_exec(), efun::db_fetch(), efun::db_handles(), master::privilege_violation()
   **/
   int db_insert_id(int handle);
}
