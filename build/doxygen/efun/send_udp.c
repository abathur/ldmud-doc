public class efun {
   /**
    * @synopsis{
    * int send_udp(string host, int port, string message)
    * int send_udp(string host, int port, int * message)
    * }
    * 
   **/
   int send_udp(string host, int port, int * message);
}
Sends the <message> in an UDP packet to the given host and port
number.

The efun causes the privilege violation ("send_udp").

Returns 1 on success, 0 on failure.

Note: On some machines a failed send_udp() will not be registered
until the next send_udp() - the latter one might return '0' even
if itself was successful.

BUGS
If the <host> is given as a fully qualified name (instead of
an IP address), the execution will block until the name is resolved.

LDMud 3.2.9 renamed this efun from send_imp(), and also changed the
   privilege violation string and the apply names.

   See Also: 
      efun::query_udp_port(), master::receive_udp()
