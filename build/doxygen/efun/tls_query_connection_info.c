public class efun {
   /**
    * If \p ob does not have a TLS connection, if the connection is still being set-up, or if \p ob is not interactive, the efun returns 0.
    * 
    * If \p ob has a TLS connection, tls_query_connection_info() returns an array that contains some parameters of \p ob connection:
    * 
    * int|string [`TLS_CIPHER`]: the cipher used
    * int        [`TLS_COMP`]:   the compression used
    * int        [`TLS_KX`]:     the key-exchange used
    * int        [`TLS_MAC`]:    the digest algorithm used
    * int|string [`TLS_PROT`]:   the protocol used
    * 
    * To translate these numbers into strings, <tls.h> offers a number of macros:
    * 
    * TLS_xxx_TABLE: a literal array of strings describing the value in question.
    * TLS_xxx_NAME(x): a macro translating the numeric result value into a string.
    * 
    * xxx: CIPHER, COMP, KX, MAC, PROT
    * 
    * @headerfile <tls.h>
    * 
    * @synopsis{
    * int * tls_query_connection_info(object ob)
    * }
    * 
    * @history{
    * introduced (3.3.474)
    * backported (3.2.11)
    * }
    * 
    * @see efun::tls_init_connection(), efun::tls_deinit_connection(), efun::tls_error(), efun::tls_query_connection_state(), efun::tls_available(), efun::tls_check_certificate(), efun::tls_refresh_certs()
   **/
   int * tls_query_connection_info(object ob);
}
