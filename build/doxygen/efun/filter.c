public class efun {
   /**
    * Call the function `<ob>-><func>()` resp. the closure \p cl for every element of the array, or mapping \p arg, and return a result made from those elements for which the function call returns TRUE. The \p extra arguments are passed as additional parameters to the function calls and must not be references of array of mapping elements (like &(i[1]) ).
    * 
    * If \p ob is omitted, or neither a string nor an object, it defaults to `this_object()`.
    * 
    * If \p arg is an array or struct, the function will be called with each of the array/struct values as first parameter, followed by the \p extra arguments. If the result from the function call is true, the array element in question is included into the efun result.
    * 
    * If the efun is used with a mapping \p map instead of a function, every array element which is key in \p map is included into the result.
    * 
    * If \p arg is a mapping, the function will be called with each of the mapping keys as first, and (if existing) the associated values as second parameter, followed by the \p extra arguments. If the result is true, the mapping element in question is included into the result.
    * 
    * Depending on the width of the mapping \p arg, the function call takes one of three forms:
    * 
    * ~~~{.c}
    * widthof(arg) == 0: ob->func(key, 0, extra...)
    *              == 1: ob->func(key, arg[key], extra...)
    *               > 1: ob->func( key
    *                            , ({ arg[key,0] ...arg[key,width-1] })
    *                            , extra...)
    * 
    * ~~~
    * The advantage of this approach is that the two types of multi-dimensional mappings (mappings with multiple values per key, and mappings of arrays) can be treated in the same way.
    * 
    * @synopsis{
    * mixed * filter(mixed *arg, string fun, string|object ob, mixed extra...)
    * mixed * filter(mixed *arg, closure cl, mixed extra...)
    * mixed * filter(mixed *arg, mapping map, mixed extra...)
    * string  filter(string arg, string fun, string|object ob, mixed extra...)
    * string  filter(string arg, closure cl, mixed extra...)
    * string  filter(string arg, mapping map, mixed extra...)
    * mapping filter(mapping arg, string func, string|object ob, mixed extra...)
    * mapping filter(mapping arg, closure cl, mixed extra...)
    * }
    * 
    * @history{
    * introduced (3.2.6) -- obsoletes filter_array() for arrays and filter_indices() with mappings.
    * changed (3.3.439) -- adds filtering of strings.
    * }
    * 
    * @see efun::filter(), efun::filter_indices(), efun::map(), efun::walk_mapping(), efun::member(), efun::m_contains()
   **/
   mapping filter(mapping arg, closure cl, mixed extra...);
}
