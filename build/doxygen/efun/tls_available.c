public class efun {
   /**
    * If the global TLS initialisation could not be set up, `tls_is_available()` returns 0, otherwise 1.
    * 
    * It is not very useful to call any other tls_* efun if this one returns 0, since there is no TLS-encryption available.
    * 
    * Most likely the global initialisation failed due to a missing or unreadable key resp. certificate-file.
    * 
    * @synopsis{
    * int tls_available()
    * }
    * 
    * @history{
    * introduced (3.3.474)
    * backported (3.2.11)
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_query_connection_state(), efun::tls_query_connection_info(), efun::tls_check_certificate(), efun::tls_refresh_certs()
   **/
   int tls_available();
}
