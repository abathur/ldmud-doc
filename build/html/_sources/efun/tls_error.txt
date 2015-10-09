.. efun:: string tls_error(int errorno)
  :preliminary:

  tls_error() returns a string describing the error behind the
  error number <errorno>.

.. history
  Introduced in LDMud 3.3.474 and later backported to 3.2.11.

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_deinit_connection`,
 :efun:`tls_query_connection_state`, :efun:`tls_query_connection_info`,
 :efun:`tls_available`, :efun:`tls_check_certificate`, :efun:`tls_refresh_certs`
