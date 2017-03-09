.. topic:: transport layer security
  :name: tls
  :experimental:
  :topics: driver

  TLS provides a way to authenticate and encrypt the data send through a network connection. TLS, which stands for Transport Layer Security, is the successor of the well known SSL (Secure Socket Layer).

  By enabling TLS during compilation of the driver you can provide a secure channel into the mud to your players.

  In difference to other solutions as "sslwrap" or "stunnel" the driver integrated approach has the advantage that the mud sees the real IP of the player, not the IP of the local mud host.

  .. usage::

    To use TLS configure your driver with :option:`--enable-tls option`. After starting your driver you have five new efuns (:efun:`tls_init_connection`, :efun:`tls_deinit_connection`, :efun:`tls_error`, :efun:`tls_query_connection_info`, :efun:`tls_query_connection_state`).

    You can switch on TLS by calling :efun:`tls_init_connection`. This can happen in three ways:

    1. in :hook:`telnet_neg`

      Advantage of this method is that you can offer TLS on a normal mud port. If you have a limited number of ports this can become important. The TLS connection will be started by the client with help of telnet option STARTTLS. Currently there are no mudclients that support this method.

      You will have to implement the telnet option STARTTLS (46) for this method. The draft for this can be found here: http://www.ietf.org/proceedings/99mar/I-D/draft-ietf-tn3270e-telnet-tls-01.txt Call :efun:`tls_init_connection` to initiate the TLS handshake.

    2. in :master:`connect`

      .. todo:: evaluate whether we can/if it's worth rendering references to a master func as ``master->function()``

      Advantage of this method is that your users can connect with any program that supports TLS/SSL. Examples are telnet-ssl, sslwrap or stunnel. Disadvantage is that you have to spend a dedicated port for this.

      You have to call :efun:`tls_init_connection` as first command after the player connected (normally in :master:`connect`).

    3. in an interactive object using a callback.

      This method is similar to method (1), but not limited to telnet: it is useful for implementing protocols that use STARTTLS like SMTP or IMAP. :efun:`tls_init_connection` can be called at any time by the interactive object.

      You must not write to the connection after calling this efun until the callback is executed (the prompt will be supressed automatically during this time).

    To test your code, you can use the openssl binary. ``openssl s_client -connect host:port`` should display your certificate and anything you write after the callback is executed. If you encounter the error message ``SSL3_GET_RECORD: wrong version number`` you're probably writing to the connection while you should not.

  .. misleading:: This manpage might be not quite up to date with the implementation.

  :history 3.3.474 introduced:
  :history 3.2.11 backported:

  .. todo:: evaluate whether there's a smart way to reference all of the tls efuns without manually listing each one separately. If I made some sort of tag/topic system I could certainly target that, but not immediately obvious how useful that could be for plaintext

  .. seealso:: :efun:`tls_available`, :efun:`tls_check_certificate`, :efun:`tls_deinit_connection`, :efun:`tls_error`, :efun:`tls_init_connection`, :efun:`tls_query_connection_info`, :efun:`tls_query_connection_state`, :efun:`tls_refresh_certs`
