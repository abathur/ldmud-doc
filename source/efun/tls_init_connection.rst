.. efun:: int tls_init_connection(object ob)
  int tls_init_connection(object ob, string fun, string|object fob, mixed extra...)
  int tls_init_connection(object ob, closure fun, mixed extra...)
  :experimental:

  Tries to start a TLS-secured connection to the interactive object :arg:`ob` (or ``this_object()`` if :arg:`ob` is not given).

  Result:
    errorcode < 0: unsuccessful, use tls_error() to get a useful description of the error
    number > 0   : the secure connection is still being set up in the background
    number == 0  : the secure connection is active.

  OpenSSL only:

    .. todo:: not sure how to render the arg refs below...

    If the callback <fun>/<fun>:<fob> is specified, it will be called once the fate of the secure connection has been determined. The first argument will be the return code from the handshake (errorcode < 0 on failure, or 0 on success), followed by the interactive object :arg:`ob` and any :arg:`extra` arguments.

  If the TLS setup fails, it is not necessary to call :efun:`tls_deinit_connection`.

  .. warning:: During the TLS handshake nothing else must be sent to the client! For the most cases (TLS-capable clients logging in) this means that the TLS handshake is the first and only thing the client gets to see while the handshake is in progress.

  The driver automatically suppresses the printing of the prompt while the TLS handshake is in progress.

  If :efun:`tls_init_connection` is called in the :master:`connect` function, the driver will either call the set callback in place of :applied:`logon`, or if no callback has been set, delay the call of :applied:`logon` until the state of the connection is clear.

  :history 3.3.474 introduced:
  :history 3.2.11 backported:
  :history 3.2.13/3.3.713 changed: streamlined the handling of secure connections during logon.

  .. seealso:: :efun:`tls_deinit_connection`, :efun:`tls_error`, :efun:`tls_query_connection_state`,:efun:`tls_query_connection_info`, :efun:`tls_available`,:efun:`tls_check_certificate`, :efun:`tls_refresh_certs`, :master:`connect`:applied:`logon`
