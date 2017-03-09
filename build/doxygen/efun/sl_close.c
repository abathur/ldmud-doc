public class efun {
   /**
    * Closes the SQLite database associated with the current object.
    * 
    * The function is available only if the driver is compiled with SQLite support. In that case, @ref driver_topics_predefined "__SQLITE__" is defined.
    * 
    * @synopsis{
    * void sl_close()
    * }
    * 
    * @history{
    * introduced (3.3.713)
    * }
    * 
    * @see efun::sl_open(), efun::sl_exec(), efun::sl_insert_id()
   **/
   void sl_close();
}
