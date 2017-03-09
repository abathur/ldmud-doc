public class efun {
   /**
    * Returns the port number the parser uses for user connections.
    * 
    * If no argument is given, the port for `this_player()` is returned. If `this_player()` doesn't exist or isn't interactive, the first port number open for connections is returned.
    * 
    * If a user object is given, the port used for its connection is returned. If a positive number is given, the :arg:>>`<<num`th port number the parser uses for connections is returned (given that there are that many ports). If -1 is given, the number of ports open for connections is returned.
    * 
    * @synopsis{
    * int query_mud_port(void)
    * int query_mud_port(object user)
    * int query_mud_port(int num)
    * }
    * 
    * @see efun::query_udp_port()
   **/
   int query_mud_port(int num);
}
