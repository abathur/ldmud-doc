.. efun:: int tls_query_connection_state(object ob)
  :experimental:

  Returns a positive number if :arg:`ob's <ob>` connection is TLS secured, 0 if it's unsecured, and a negative number if the TLS connection is still being set-up.

  :history 3.3.474 introduced:
  :history 3.2.11 backported:

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_deinit_connection`, :efun:`tls_error`, :efun:`tls_query_connection_info`, :efun:`tls_available`, :efun:`tls_check_certificate`, :efun:`tls_refresh_certs`
