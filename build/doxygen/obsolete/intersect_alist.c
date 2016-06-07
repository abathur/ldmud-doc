public class efun {
   /**
    * Does a fast set intersection on alist key vectors (NOT on full alists!).
    * The operator '&' does set intersection on arrays in general.
    * 
    * The function is available only if the driver is compiled with
    * alist support. In that case, __ALISTS__ is defined.
    * 
    * @synopsis{
    * mixed * intersect_alist(mixed * list1, mixed * list2)
    * }
    * 
    * @usage{
    * new_list = intersect_alist(list1, list2);
    * }
    * 
    * @history{
    * changed (3.3) -- made this an optional efun.
    * }
    * 
    * @see efun::filter_array(), efun::assoc(), efun::insert_alist(), efun::map_array(), efun::member_array(), efun::order_alist(), efun::sort_array(), efun::unique_array()
   **/
   mixed * intersect_alist(mixed * list1, mixed * list2);
}
