public class master {
   /**
    * Notify the master about an immediate shutdown. If \p crash_reason is 0, it is a normal shutdown, otherwise it is a crash and \p crash_reason gives a hint at the reason.
    * 
    * The function has the opportunity to perform any cleanup operation, like informing the mudwho server that the mud is down. This can not be done when master::remove_player() is called because the udp connectivity is already gone then.
    * 
    * - If the gamedriver shuts down normally, this is the last function called before the mud shuts down the udp connections and the accepting socket for new players.
    * - If the gamedriver crashes, this is the last function called before the mud attempts to dump core and exit. The following crash reasons are defined:
    * - "Fatal Error": an internal sanity check failed.
    * @par warning: Since the driver is in an unstable state, this function may not be able to run to completion!
    * 
    * 
    * @synopsis{
    * varargs void notify_shutdown(string crash_reason)
    * }
    * 
    * @history{
    * changed (3.2.9) -- added the crash_reason argument and that the function is called for a crash at all.
    * }
    * 
    * @see master::slow_shut_down(), master::remove_player()
   **/
   varargs void notify_shutdown(string crash_reason);
}
