.. efun:: int * tls_query_connection_info(object ob)
  :experimental:
  :include: <tls.h>

  If :arg:`ob` does not have a TLS connection, if the connection is still being set-up, or if :arg:`ob` is not interactive, the efun returns 0.

  If :arg:`ob` has a TLS connection, tls_query_connection_info() returns an array that contains some parameters of :arg:`ob's <ob>` connection:

    int|string [:macro:`TLS_CIPHER`]: the cipher used
    int        [:macro:`TLS_COMP`]:   the compression used
    int        [:macro:`TLS_KX`]:     the key-exchange used
    int        [:macro:`TLS_MAC`]:    the digest algorithm used
    int|string [:macro:`TLS_PROT`]:   the protocol used

  To translate these numbers into strings, <tls.h> offers a number of macros:

    TLS_xxx_TABLE: a literal array of strings describing the value in question.
    TLS_xxx_NAME(x): a macro translating the numeric result value into a string.

    xxx: CIPHER, COMP, KX, MAC, PROT

  :history 3.3.474 introduced:
  :history 3.2.11 backported:

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_deinit_connection`, :efun:`tls_error`, :efun:`tls_query_connection_state`, :efun:`tls_available`, :efun:`tls_check_certificate`, :efun:`tls_refresh_certs`
