public class efun {
   /**
    * `ob->func()` is called resp. \p cl applied to every element in the mapping, with first argument being the key of the element, and then the extra args that were given to filter_indices (these args must not be protected references like &(i[0]). If the function returns true, the element is added to the result mapping. \p ob can also be an object_name of an object.
    * 
    * If \p ob is omitted, or neither a string nor an object, it defaults to `this_object()`.
    * 
    * Histoy 3.2.6 changed: 
    * renamed from `filter_mapping()` and generalised by efun::filter().
    * 
    * @synopsis{
    * mapping filter_indices(mapping, string func, string|object ob, ...)
    * mapping filter_indices(mapping, closure cl, ...)
    * }
    * 
    * @see efun::filter(), efun::map(), efun::map_indices(), efun::walk_mapping(), efun::member(), efun::m_contains()
   **/
   mapping filter_indices(mapping, closure cl, ...);
}
