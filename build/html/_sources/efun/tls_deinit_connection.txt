.. efun:: void tls_deinit_connection(object ob)
  :preliminary:

DESCRIPTION
tls_deinit_connection() shuts down a TLS connection to
the interactive object <ob> (or this_object() if <ob> is not
given) but the connection is not closed.

Under normal circumstances there is no need to use this efun: most
clients operate in either secure or unsecure mode, but don't allow
switching connection security on the fly.

.. history
Introduced in LDMud 3.3.474 and later backported to 3.2.11.

  .. seealso:: :efun:`tls_init_connection`, :efun:`tls_error`, :efun:`tls_query_connection_state`,
 :efun:`tls_query_connection_info`, :efun:`tls_available`,
 :efun:`tls_check_certificate`, :efun:`tls_refresh_certs`
