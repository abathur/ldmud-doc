.. applied:: int logon(void)
  int logon(int flag)

  When the driver created a new connection (either by accepting it or by creating it with :efun:`net_connect`) and bound it to an object, it then calls `logon()` in that object.

  The method should return 0 on failure, and everything else on success.

  If the driver attempted to create a connection in the background and failed, it will call `logon(-1)` in the intended object to inform the mudlib about the failure.

  If the master attempted a secure connection in :efun:`connect` and did not set an explicit TLS callback, the call to `logon()` won't happen until the TLS handshake is complete. If the master set a TLS callback, that will be executed in place of `logon()`.

  :history 3.2.10 changed: added the extended meaning for :efun:`net_connect`.
  :history 3.2.13/3.3.713 changed: streamlined the handling of secure connections during logon.

  .. seealso:: :master:`connect`, :efun:`net_connect`, :efun:`exec`, :efun:`tls_init_connection`
