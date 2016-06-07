public class efun {
   /**
    * Give the ip-name for user the current user or for the
    * optional argument ob. An asynchronous process 'hname' is used
    * to find out these names in parallel. If there are any failures
    * to find the ip-name, then the ip-number is returned instead.
    * 
    * @synopsis{
    * string query_ip_name(object ob)
    * }
    * 
    * @see efun::query_ip_number()
   **/
   string query_ip_name(object ob);
}
