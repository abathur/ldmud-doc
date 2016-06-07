public class efun {
   /**
    * @synopsis{
    * void walk_mapping(mapping m, string func, mixed extra, ...)
    * void walk_mapping(mapping m, string func, string|object ob, mixed extra, ...)
    * void walk_mapping(mapping m, closure cl, mixed extra, ...)
    * }
    * 
   **/
   void walk_mapping(mapping m, closure cl, mixed extra, ...);
}
Calls ob->func(key, value1, ..., valueN, extra,...) resp. applies
the closure to every entry in the mapping. The keys are passed
by value, the values are passed by reference and can be
changed in the function.

Any number of extra arguments is accepted and passed. These arguments
must not be protected references like &(i[]).

If <ob> is omitted, or neither a string nor an object, it
defaults to this_object().

Introduced in @subpage driver_mailto:3.2@61 "3.2@61"

   See Also: 
      efun::map(), efun::filter()
