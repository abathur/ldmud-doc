public class efun {
   /**
    * After inserting a line into a table with an `AUTO_INCREMENT` field, this efun can be used to return the (new) value of the `AUTO_INCREMENT` field.
    * 
    * The function is available only if the driver is compiled with SQLite support. In that case, @ref driver_topics_predefined "__SQLITE__" is defined.
    * 
    * @synopsis{
    * int sl_insert_id()
    * }
    * 
    * @history{
    * introduced (3.3.713)
    * }
    * 
    * @see efun::sl_open(), efun::sl_exec(), efun::sl_close()
   **/
   int sl_insert_id();
}
