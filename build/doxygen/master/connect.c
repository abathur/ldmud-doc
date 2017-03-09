public class master {
   /**
    * Return a login object that the requested connection should be bound to.
    * 
    * At call time, the connection is bound to the master object, and will be re-bound to the returned object.
    * 
    * The lfun applied::logon() will be applied to the login object after binding the connection to it. That lfun has to return != 0 to indicate success.
    * 
    * If master::connect() initiates a secure connection without setting a callback, and the connection is still handshaking at the time master::connect() returns, the driver will delay the call to applied::logon() until the handshake either succeeds or fails.
    * 
    * @synopsis{
    * object connect(void)
    * }
    * 
    * @history{
    * changed (3.2.13/3.3.713) -- streamlined the handling of secure connections during logon.
    * }
    * 
    * @see applied::logon(), master::disconnect(), efun::interactive(), efun::exec(), efun::net_connect(), efun::tls_init_connection()
   **/
   object connect(void);
}
