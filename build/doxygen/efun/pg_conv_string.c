public class efun {
   /**
    * Convert the string \p str into a string that is correctly interpretated for usage as a string in efun::pg_query(), e.g. `'` is replaced with `\'` and so on.
    * 
    * The function is available only if the driver is compiled with PostgreSQL support. In that case, @ref driver_topics_predefined "__PGSQL__" is defined.
    * 
    * The efun triggers a privilege violation ("pgsql", "pg_connect").
    * 
    * @synopsis{
    * string pg_conv_string(string str)
    * }
    * 
    * @history{
    * introduced (3.3.708)
    * }
    * 
    * @see efun::pg_query(), efun::pg_pending(), efun::pg_conv_string(), efun::pg_close(), master::privilege_violation()
   **/
   string pg_conv_string(string str);
}
