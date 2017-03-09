public class efun {
   /**
    * Reload the certificates and certificate revocation information.
    * 
    * If there are no key and certificate files to be found, this efun will keep the current keys and certificates, to keep TLS working. CAs and CRLs are cleared and reloaded in any case.
    * 
    * @par warning: when using GnuTLS, a call to efun::tls_refresh_certs() while a connection is in the middle of a TLS handshake might cause an incorrect key to be used.
    * 
    * @synopsis{
    * void tls_refresh_certs()
    * }
    * 
    * @history{
    * introduced (3.3.714/3.2.15)
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_error(), efun::tls_query_connection_state(), efun::tls_query_connection_info(), efun::tls_available(), efun::tls_check_certificate()
   **/
   void tls_refresh_certs();
}
