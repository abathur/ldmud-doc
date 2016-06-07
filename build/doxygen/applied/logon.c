public class applied {
   /**
    * When the driver created a new connection (either by accepting it or by creating it with efun::net_connect()) and bound it to an object, it then calls @alogon()` in that object.
    * 
    * The method should return 0 on failure, and everything else on success.
    * 
    * If the driver attempted to create a connection in the background and failed, it will call @alogon(-1)` in the intended object to inform the mudlib about the failure.
    * 
    * If the master attempted a secure connection in `connect()` and did not set an explicit TLS callback, the call to @alogon()` won't happen until the TLS handshake is complete. If the master set a TLS callback, that will be executed in place of @alogon()`.
    * 
    * @synopsis{
    * int logon(void)
    * int logon(int flag)
    * }
    * 
    * @history{
    * changed (3.2.10) -- added the extended meaning for net_connect().
    * changed (3.2.13/3.3.713) -- streamlined the handling of secure connections during logon.
    * }
    * 
    * @see master::connect(), efun::net_connect(), efun::exec(), efun::tls_init_connection()
   **/
   int logon(int flag);
}
