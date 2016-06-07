public class efun {
   /**
    * Similar to map(), but calls arr[n]->fun(extra,...). The returned value
    * replaces the object/string in returned array.
    * <arr> may contain a mixture of objects and object names as well.
    * 
    * Any number of extra arguments is allowed, which are all
    * passed. 0-entries in arr are ignored.
    * 
    * @synopsis{
    * mixed * map_objects(object *arr, string fun, mixed extra, ...)
    * mixed * map_objects(string *arr, string fun, mixed extra, ...)
    * }
    * 
    * @see efun::map(), efun::filter(), efun::filter_objects()
   **/
   mixed * map_objects(string *arr, string fun, mixed extra, ...);
}
