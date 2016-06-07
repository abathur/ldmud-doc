public class efun {
   /**
    * ob->func() is called resp. cl applied to every element in the mapping,
    * with the key of the element as first argument, and then the extra args
    * that were given to map_mapping (these args must not be protected
    * references like &(i[0])).  The data item in the mapping is replaced by
    * the return value of the function. ob can also be a file_name of an
    * object.
    * 
    * If <ob> is omitted, or neither a string nor an object, it
    * defaults to this_object().
    * 
    * Note that if mapping m has more than one value per key, these
    * are ignored: the resulting mapping always has one value per key.
    * 
    * Also note that the behaviour of this function is different from
    * map_array().
    * 
    * @synopsis{
    * mapping map_mapping(mapping m, string func, string|object ob, ...)
    * mapping map_mapping(mapping m, closure cl, ...)
    * }
    * 
    * @usage{
    * m = mkmapping(users());
    * m = map_mapping(m, #'environment);
    * }
    * 
    * @history{
    * changed (3.2.6) -- renamed to map_indices()
    * changed (3.2.9) -- not available if driver is compiled without USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see efun::map(), efun::filter(), efun::filter_indices(), efun::walk_mapping(), efun::member(), efun::m_contains()
   **/
   mapping map_mapping(mapping m, closure cl, ...);
}
