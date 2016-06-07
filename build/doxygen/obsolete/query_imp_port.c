public class efun {
   /**
    * Returns the port number that is used for the inter mud
    * protocol.
    * 
    * is available if the driver is compiled with USE_DEPRECATED.
    * :history 3.3 removed:
    * 
    * @synopsis{
    * int query_imp_port(void)
    * }
    * 
    * @history{
    * changed (3.2.9) -- renamed this efun to query_udp_port(). This version
    * }
    * 
    * @see efun::send_udp(), master::receive_udp()
   **/
   int query_imp_port(void);
}
