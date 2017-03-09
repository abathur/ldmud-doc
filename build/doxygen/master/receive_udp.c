public class master {
   /**
    * Handle a received UDP message.
    * 
    * This function is called for every message received on the UDP port. Usually it is passed on to some object that handles inter-mud communications.
    * 
    * @synopsis{
    * void receive_udp(string host, string msg, int hostport)
    * }
    * 
    * @history{
    * changed (3.2.1) -- added 'hostport' argument
    * changed (3.2.9) -- renamed to receive_udp() from receive_imp().
    * }
    * 
    * @see efun::send_udp(), efun::query_udp_port()
   **/
   void receive_udp(string host, string msg, int hostport);
}
