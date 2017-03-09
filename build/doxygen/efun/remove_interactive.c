public class efun {
   /**
    * Close the connection to the interactive object ob.
    * 
    * For the time of the LPC execution, the object is only marked internally as 'about to be closed', meaning that while all output will be redirected to stdout, the actual network connection will continue to exist until the LPC execution ends.
    * 
    * @synopsis{
    * void remove_interactive(object ob)
    * }
    * 
    * @see master::connect(), applied::logon(), master::disconnect()
   **/
   void remove_interactive(object ob);
}
