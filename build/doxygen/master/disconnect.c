public class master {
   /**
    * Handle the loss of the IP connection for the (formerly) interactive object \p ob. The connection can be lost because the the underlying transport connection was lost ('netdead'), or because of a call to efun::exec() or efun::remove_interactive().
    * 
    * \p remaining is a string holding the remaining unread input data from the connection, if any. This data is unprocessed just as it was received.
    * 
    * The connection will be unbound upon return from this call, so for the time of this call, `interactive(ob)` will still return TRUE even if the actual network connection has already been lost.
    * 
    * This method is not called if the object has been destructed already.
    * 
    * @synopsis{
    * void disconnect(object ob, string remaining)
    * }
    * 
    * @history{
    * changed (3.3.713) -- added the second argument for the remaining input data.
    * }
    * 
    * @see master::connect(), master::remove_player(), efun::remove_interactive(), efun::exec(), efun::interactive()
   **/
   void disconnect(object ob, string remaining);
}
