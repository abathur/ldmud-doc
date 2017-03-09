public class efun {
   /**
    * Call the function `<ob>-><func>()` resp. the closure \p cl for every element of the string, array, struct or mapping \p arg, and return a result made up from the returned values.
    * 
    * If \p ob is omitted, or neither a string nor an object, it defaults to `this_object()`.
    * 
    * If \p arg is an string, array or struct, the function will be called with each of the array/struct elements as first parameter, followed by the \p extra arguments. The result of the efun is an array/struct with all the results returned from the function calls. Thus the operation could be described as:
    * 
    * ~~~{.c}
    * foreach(index) result[index] = ob->func(arg[index], extra...)
    * 
    * ~~~
    * If \p arg is an string/array/struct, and a mapping is specified instead of a function, the result is an array/struct with the values found in the mapping for the original values, resp. with the original values for which no mapping entry exists. If a column index `idx` is given, that column of the mapping is used. In other words:
    * 
    * ~~~{.c}
    * foreach(index)
    *   if (arg[index] exists as key in map)
    *     result[index] = map[arg[index]] or map[arg[index], idx]
    *   else
    *     result[index] = arg[index]
    * 
    * ~~~
    * If \p arg is a string, the only allowed replacement values are numbers, of which only the lower 8 bit will be considered.
    * 
    * If \p arg is a mapping, the function will be called with each of the mapping keys as first, and (if existing) the associated values as second parameter, followed by the \p extra arguments (these must not be protected references like &(i[0]). The result of the efun is a mapping of all results of the function calls, stored under their corresponding key.
    * 
    * Depending on the width of the mapping \p arg, the operation can be described as:
    * 
    * ~~~{.c}
    * foreach (key in arg)
    *   switch (widthof(arg))
    *   case 0:
    *     result[key] = ob->func(key, 0, extra...)
    *   case 1:
    *     result[key] = ob->func(key, arg[key], extra...)
    *   else  :
    *     result[key] = ob->func( key
    *                           , ({ arg[key,0] ...arg[key,width-1] })
    *                           , extra...)
    * 
    * ~~~
    * The advantage of this approach is that the two types of multi-dimensional mappings (mappings with multiple values per key, and mappings of arrays) can be treated in the same way.
    * 
    * Caution: the resulting mapping _always_ has one value per key.
    * @par note: This efun behaves like `map_array()`, but used with mappings generalises efun::map_indices()!
    * 
    * @synopsis{
    * mixed * map(mixed *arg, string func, string|object ob, mixed extra...)
    * mixed * map(mixed *arg, closure cl, mixed extra...)
    * mixed * map(mixed *arg, mapping m [, int idx])
    * mixed * map(struct arg, string func, string|object ob, mixed extra...)
    * mixed * map(struct arg, closure cl, mixed extra...)
    * mixed * map(struct arg, mapping m [, int idx])
    * mapping map(mapping arg, string func, string|object ob, mixed extra...)
    * mapping map(mapping arg, closure cl, mixed extra...)
    * string map(string arg, string func, string|object ob, mixed extra...)
    * string map(string arg, closure cl, mixed extra...)
    * string map(string arg, mapping m [, int idx])
    * }
    * 
    * @usage{
    * ~~~{.c}
    * arr = ({ 1, 2, 3, 4 });
    * m = ([ 1:-1, 3:-3 ]);
    * 
    * map(arr, #'%, 2); // returns ({ 1, 0, 1, 0 })
    * map(arr, m);      // returns ({ -1, 2, -3, 4 })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6) -- obsoletes map_array().
    * changed (3.2.8) -- added the feature of mapping an array through a mapping.
    * changed (3.3.439) -- added mapping of strings.
    * changed (3.3.719) -- added the idx parameter for mapping through mappings.
    * }
    * 
    * @see efun::filter(), efun::filter_indices(), efun::map_indices(), efun::map_objects()
   **/
   string map(string arg, mapping m [, int idx]);
}
