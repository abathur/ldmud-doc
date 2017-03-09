public class master {
   /**
    * Should return 1 if `previous_object()` (the one that called efun::query_snoop() is allowed to query whether ob is being snooped, 0 if not.
    * 
    * The master object is always allowed to use efun::query_snoop().
    * 
    * @synopsis{
    * int valid_query_snoop(object ob)
    * }
    * 
    * @see master::valid_snoop(), efun::query_snoop(), efun::snoop()
   **/
   int valid_query_snoop(object ob);
}
