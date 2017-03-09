public class efun {
   /**
    * `ob->func()` is called resp. cl applied to every element in the mapping, with the key of the element as first argument, and then the extra args that were given to map_indices (these args must not be protected references like &(i[0])). The data item in the mapping is replaced by the return value of the function. ob can also be a file_name of an object.
    * 
    * If \p ob is omitted, or neither a string nor an object, it defaults to `this_object()`.
    * 
    * Note that if mapping m has more than one value per key, these are ignored: the resulting mapping always has one value per key.
    * 
    * Also note that the behaviour of this function is different from `map(<array>)`.
    * 
    * @synopsis{
    * mapping map_indices(mapping m, string func, string|object ob, ...)
    * mapping map_indices(mapping m, closure cl, ...)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * m = mkmapping(users());
    * m = map_indices(m, #'environment);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6) -- renamed from map_mapping() and complemented by map.
    * }
    * 
    * @see efun::map(), efun::filter(), efun::filter_indices(), efun::walk_mapping(), efun::member(), efun::m_contains()
   **/
   mapping map_indices(mapping m, closure cl, ...);
}
