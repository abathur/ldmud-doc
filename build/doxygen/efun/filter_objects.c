public class efun {
   /**
    * Similar to filter_array() but calls arr[n]->fun(extra, ...).
    * If the call returns != 0, the object arr[n] ist included in
    * the returned array.
    * 0-entries in arr are ignored.
    * 
    * @synopsis{
    * object * filter_objects(object *arr, string fun, mixed extra, ...)
    * }
    * 
    * @see efun::filter(), efun::map(), efun::map_objects()
   **/
   object * filter_objects(object *arr, string fun, mixed extra, ...);
}
