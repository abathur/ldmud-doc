public class efun {
   /**
    * Checks the certificate of the secured connection bound to \p obj (default is the current object). An error is thrown if \p obj is not interactive or TLS is not available.
    * 
    * An error is also thrown if \p obj doesn't have a secure connection up and running.
    * 
    * Otherwise, the result is an array with these values:
    * 
    * @par note: An X509 certificate can have more than one object with the same name.
    * 
    * @synopsis{
    * mixed * tls_check_certificate(object obj)
    * mixed * tls_check_certificate(object obj, int extra)
    * }
    * 
    * @history{
    * introduced (3.3.672/3.2.11)
    * changed (3.3.711/3.2.12) -- modified the behaviour to return the low-level API result value, and to throw an error if the connection is not secure.
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_error(), efun::tls_query_connection_state(), efun::tls_query_connection_info(), efun::tls_available(), efun::tls_refresh_certs()
   **/
   mixed * tls_check_certificate(object obj, int extra);
}
