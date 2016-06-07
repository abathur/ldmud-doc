public class efun {
   /**
    * Return non-zero if ob is an interactive user. If ob is omitted,
    * this_object() will be used. The return value is 1 if the
    * object is interactive, else 0.
    * 
    * @synopsis{
    * int interactive()
    * int interactive(object ob)
    * }
    * 
    * @see efun::query_once_interactive(), efun::query_ip_number(), efun::query_ip_name(), efun::query_idle()
   **/
   int interactive(object ob);
}
