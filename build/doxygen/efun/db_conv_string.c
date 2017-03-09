public class efun {
   /**
    * Convert the string \p str into a string that is correctly interpretated for usage as a string in efun::db_exec(), e.g. ' is replaced with ' and so on.
    * 
    * The function is available only if the driver is compiled with mySQL support. In that case, @ref driver_topics_predefined "__MYSQL__" is defined.
    * 
    * @synopsis{
    * string db_conv_string(string str)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::db_affected_rows(), efun::db_close(), efun::db_coldefs(), efun::db_connect(), efun::db_exec(), efun::db_error(), efun::db_fetch(), efun::db_handles(), efun::db_insert_id()
   **/
   string db_conv_string(string str);
}
