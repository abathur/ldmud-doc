public class efun {
   /**
    * Opens the file \p filename for use as a SQLite database. The file will be created if it doesn't exist. Only one open file per object is allowed. On success this function returns 1, otherwise an error is usually thrown.
    * 
    * The function is available only if the driver is compiled with SQLite support. In that case, @ref driver_topics_predefined "__SQLITE__" is defined.
    * 
    * @synopsis{
    * int sl_open(string filename)
    * }
    * 
    * @history{
    * introduced (3.3.713)
    * }
    * 
    * @see efun::sl_exec(), efun::sl_insert_id(), efun::sl_close()
   **/
   int sl_open(string filename);
}
