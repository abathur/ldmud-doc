public class efun {
   /**
    * Evaluates the closure \p cl with the following arguments. If the last argument is an array or struct, it will be flattened: ie. the array/struct itself will be removed and its contents added to the argument list of \p cl.
    * 
    * If \p cl is not a closure, it will simply be returned (and all other arguments are ignored).
    * 
    * @synopsis{
    * mixed apply(closure cl, ...)
    * }
    * 
    * @usage{
    * The flattening of the last argument is the important difference between efun::apply() and efun::funcall(). For example:
    * 
    * ~~~{.c}
    * mixed eval(object ob, string func, mixed *args)
    * {
    *   return apply(#'call_other, ob, func, args);
    * }
    * 
    * ~~~
    * This will result in calling:
    * 
    * ~~~{.c}
    * ob->func(args[0],args[1],...,args[sizeof(args)-1]).
    * 
    * ~~~
    * Using efun::funcall() instead of efun::apply() would have given us:
    * 
    * ~~~{.c}
    * ob->func(args).
    * 
    * ~~~
    * Of course, with the '...' operator we could also write:
    * 
    * ~~~{.c}
    * mixed eval(object ob, string func, mixed *args)
    * {
    *   return funcall(#'call_other, ob, func, args...);
    * }
    * 
    * ~~~
    * and achieve the same result.
    * 
    * }
    * 
    * @history{
    * introduced (3.2@70)
    * changed (3.2.8) -- adds the returning of a non-closure as first argument.
    * changed (3.3) -- added the '...' operator and thus made apply in fact redundant.
    * changed (3.3.266) -- added support for structs.
    * }
    * 
    * @see efun::funcall(), @ref driver_syntax_closures "closure", @ref driver_syntax_varargs "varargs"
   **/
   mixed apply(closure cl, ...);
}
