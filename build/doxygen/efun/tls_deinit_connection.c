public class efun {
   /**
    * Shuts down a TLS connection to the interactive object \p ob (or `this_object()` if \p ob is not given) but the connection is not closed.
    * 
    * Under normal circumstances there is no need to use this efun: most clients operate in either secure or unsecure mode, but don't allow switching connection security on the fly.
    * 
    * @synopsis{
    * void tls_deinit_connection(object ob)
    * }
    * 
    * @history{
    * introduced (3.3.474)
    * backported (3.2.11)
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_error(), efun::tls_query_connection_state(), efun::tls_query_connection_info(), efun::tls_available(), efun::tls_check_certificate(), efun::tls_refresh_certs()
   **/
   void tls_deinit_connection(object ob);
}
