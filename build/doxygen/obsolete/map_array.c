public class efun {
   /**
    * Returns an array holding the items of arr mapped through
    * ob->fun(element, extra) resp. the closure cl. The function fun
    * in ob is called for each element in arr with that element as
    * parameter. A second parameter extra is sent in each call if
    * given. ob can be an object or a string. Principal function:
    * 
    * foreach (index) arr[index] = ob->fun(arr[index],extra);
    * 
    * The value returned by ob->fun(array[index],extra) replaces the
    * existing element in the array. If arr is not an array, then 0
    * will be returned.
    * 
    * The extra argument is optional and must not be a protected reference
    * like &(i[0]). If <ob> is omitted, or neither a string nor an object,
    * it defaults to this_object().
    * 
    * @synopsis{
    * mixed *map_array(mixed *arr, string fun, string|object ob, mixed extra)
    * mixed *map_array(mixed *arr, closure cl, mixed extra)
    * }
    * 
    * @usage{
    * This will create an array holding all uids of the current
    * users:
    * string ask_for_uid(object obj) {
    *    return getuid(obj);
    * }
    * 
    * void func() {
    *    string *names;
    *    names = map_array(users(), "ask_for_uid", this_object());
    *    /* equivalent but a bit smaller and faster is the following */
    *    names = map_array(users(), #'getuid );
    *    ...
    * }
    * }
    * 
    * @history{
    * changed (3.2.6) -- obsoleted by map().
    * changed (3.2.9) -- not available if driver is compiled without USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see efun::filter(), efun::filter_objects(), efun::assoc(), efun::intersect_alist(), efun::insert_alist(), efun::map(), efun::map_objects(), efun::member(), efun::order_alist(), efun::sort_array(), efun::unique_array()
   **/
   mixed *map_array(mixed *arr, closure cl, mixed extra);
}