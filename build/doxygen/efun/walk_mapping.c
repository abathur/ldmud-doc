public class efun {
   /**
    * Calls `ob->func(key, value1, ..., valueN, extra,...)` resp. applies the closure to every entry in the mapping. The keys are passed by value, the values are passed by reference and can be changed in the function.
    * 
    * Any number of extra arguments is accepted and passed. These arguments must not be protected references like `&(i[])`.
    * 
    * If \p ob is omitted, or neither a string nor an object, it defaults to `this_object()`.
    * 
    * @synopsis{
    * void walk_mapping(mapping m, string func, mixed extra, ...)
    * void walk_mapping(mapping m, string func, string|object ob, mixed extra, ...)
    * void walk_mapping(mapping m, closure cl, mixed extra, ...)
    * }
    * 
    * @history{
    * introduced (3.2@61)
    * }
    * 
    * @see efun::map(), efun::filter()
   **/
   void walk_mapping(mapping m, closure cl, mixed extra, ...);
}
