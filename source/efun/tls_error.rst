.. efun:: string tls_error(int errorno)
  :experimental:

  Returns a string describing the error behind the error number :arg:`errorno`.

  :history 3.3.474 introduced:
  :history 3.2.11 backported:

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_deinit_connection`, :efun:`tls_query_connection_state`, :efun:`tls_query_connection_info`, :efun:`tls_available`, :efun:`tls_check_certificate`, :efun:`tls_refresh_certs`
