.. efun:: void tls_deinit_connection(object ob)
  :experimental:

  Shuts down a TLS connection to the interactive object :arg:`ob` (or ``this_object()`` if :arg:`ob` is not given) but the connection is not closed.

  Under normal circumstances there is no need to use this efun: most clients operate in either secure or unsecure mode, but don't allow switching connection security on the fly.

  :history 3.3.474 introduced:
  :history 3.2.11 backported:

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_error`, :efun:`tls_query_connection_state`, :efun:`tls_query_connection_info`, :efun:`tls_available`, :efun:`tls_check_certificate`, :efun:`tls_refresh_certs`
