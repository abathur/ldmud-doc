public class efun {
   /**
    * tls_query_connection_state() returns a positive number if <ob>'s
    * connection is TLS secured, 0 if it's unsecured, and a negative number
    * if the TLS connection is still being set-up.
    * 
    * Introduced in LDMud 3.3.474 and later backported to 3.2.11.
    * 
    * @synopsis{
    * int tls_query_connection_state(object ob)
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_error(), efun::tls_query_connection_info(), efun::tls_available(), efun::tls_check_certificate(), efun::tls_refresh_certs()
   **/
   int tls_query_connection_state(object ob);
}
