public class efun {
   /**
    * @synopsis{
    * int query_mud_port(void)
    * int query_mud_port(object user)
    * int query_mud_port(int num)
    * }
    * 
   **/
   int query_mud_port(int num);
}
Returns the port number the parser uses for user connections.

If no argument is given, the port for this_player() is
returned. If this_player() is not existing or not interactive,
the first port number open for connections is returned.

If an user object is given, the port used for its connection
is returned.
If a positive number is given, the <num>th port number the
parser uses for connections is returned (given that there are
that many ports).
If -1 is given, the number of ports open for connections is
returned.

   See Also: 
      efun::query_udp_port()
