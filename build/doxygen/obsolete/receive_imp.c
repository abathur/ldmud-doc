public class efun {
   /**
    * Handle a received IMP message.
    * 
    * This function is called for every message received on the IMP
    * port. Usually it is passed on to some object that handles
    * inter mud communications.
    * 
    * The driver first calls receive_udp(). If that method doesn't exist
    * and if the driver is compiled with USE_DEPRECATED, it will then
    * call receive_imp().
    * 
    * @synopsis{
    * void receive_imp(string host, string msg, int hostport)
    * }
    * 
    * @history{
    * changed (3.2.1) -- 'hostport' argument was added
    * changed (3.2.9) -- renamed this method to receive_udp(); this old version is supported if the driver is compiled with USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see efun::send_udp(), efun::query_udp_port()
   **/
   void receive_imp(string host, string msg, int hostport);
}
