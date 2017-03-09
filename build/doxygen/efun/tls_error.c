public class efun {
   /**
    * Returns a string describing the error behind the error number \p errorno.
    * 
    * @synopsis{
    * string tls_error(int errorno)
    * }
    * 
    * @history{
    * introduced (3.3.474)
    * backported (3.2.11)
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_query_connection_state(), efun::tls_query_connection_info(), efun::tls_available(), efun::tls_check_certificate(), efun::tls_refresh_certs()
   **/
   string tls_error(int errorno);
}
