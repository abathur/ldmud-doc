public class efun {
   /**
    * Evaluates the closure. The extra args will be passed as args to the closure. If cl is not a closure, it will simply be returned.
    * 
    * @synopsis{
    * mixed funcall(closure cl, mixed arg ...)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mixed eval(object ob, string func, mixed *args)
    * {
    *     return funcall(#'call_other, ob, func, args);
    * }
    * 
    * ~~~
    * This will result in calling:
    * 
    * ~~~{.c}
    * ob->func(args).
    * 
    * ~~~
    * In combination with the '...' operator, the functionality of efun::apply() can be implemented:
    * 
    * ~~~{.c}
    * mixed eval(object ob, string func, mixed *args)
    * {
    *     return funcall(#'call_other, ob, func, args...);
    * }
    * 
    * ~~~
    * will result in calling:
    * 
    * ~~~{.c}
    * ob->func(args[0],args[1],...,args[sizeof(args)-1])
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2@70)
    * changed (3.2.1) -- returns a non-closure unchanged even when args are given.
    * }
    * 
    * @see efun::apply(), efun::quote()
   **/
   mixed funcall(closure cl, mixed arg ...);
}
