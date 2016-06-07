public class efun {
   /**
    * Sends The message in an UDP packet to the given host and port
    * number.
    * 
    * The message can be given either as string, or as array of
    * bytes. The latter variant allows to send binary data as well.
    * 
    * The efun causes a privilege violation. If USE_DEPRECATED is in effect,
    * it first tries privilege violation ("send_imp"), and, if this one
    * returns 0, then it tries privilege violation ("send_udp").
    * If USE_DEPRECATED is not in effect, it just tries privilege
    * violation ("send_udp").
    * 
    * Returns 1 on success, 0 on failure.
    * 
    * @par note:On some machines a failed send_imp() will not be registered
    * until the next send_imp() - the latter one might return '0' even
    * if itself was successful.
    * 
    * @synopsis{
    * int send_imp(string host, int port, string message)
    * int send_imp(string host, int port, int * message)
    * }
    * 
    * @history{
    * changed (3.2.9) -- renamed this efun to send_udp(), and also changed the privilege violation string and the apply names. This old version is available if the driver is compiled with USE_DEPRECATED.
    * removed (LDMud)
    * }
    * 
    * @see efun::query_udp_port(), master::receive_udp(), efun::receive_imp()
   **/
   int send_imp(string host, int port, int * message);
}
