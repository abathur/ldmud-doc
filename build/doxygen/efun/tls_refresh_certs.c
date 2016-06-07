public class efun {
   /**
    * @synopsis{
    * void tls_refresh_certs()
    * }
    * 
   **/
   void tls_refresh_certs();
}
Reload the certificates and certificate revocation information.

If there are no key and certificate files to be found, this efun
will keep the current keys and certificates, to keep TLS working.
CAs and CRLs are cleared and reloaded in any case.

Note that when using GnuTLS a call to tls_refresh_certs()
while a connection is in the middle of a TLS handshake might
cause an incorrect key to be used.

Introduced in LDMud 3.3.714/3.2.15.

      See Also: 
         efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_error(),

   efun::tls_query_connection_state(), efun::tls_query_connection_info(),
   efun::tls_available(), efun::tls_check_certificate(), mudlib/psyc-tls.c
