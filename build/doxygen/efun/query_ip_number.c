public class efun {
   /**
    * Give the ip-number for the current user or the optional
    * argument ob.
    * 
    * If ob is given as reference (and it must be a valid object then),
    * it will upon return be set to the struct sockaddr_in of the queried
    * object, represented by an array of integers, one integer per
    * address byte:
    * 
    * ob[0.. 1]: sin_family
    * ob[2.. 3]: sin_port
    * ob[4.. 7]: sin_addr
    * ob[8..15]: undefined.
    * 
    * The return of the struct sockaddr_in was introduced in @subpage driver_mailto:3.2.1@81 "3.2.1@81".
    * 
    * @synopsis{
    * string query_ip_number(object  ob)
    * string query_ip_number(mixed & ob)
    * }
    * 
    * @see efun::query_ip_name()
   **/
   string query_ip_number(mixed & ob);
}
