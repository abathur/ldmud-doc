public class efun {
   /**
    * @synopsis{
    * mixed funcall(closure cl, mixed arg ...)
    * }
    * 
   **/
   mixed funcall(closure cl, mixed arg ...);
}
Evaluates the closure. The extra args will be passed as args
to the closure. If cl is not a closure, it will simply be
returned.

EXAMPLES
mixed eval(object ob, string func, mixed >>*<<args)
{

   return funcall(#'call_other, ob, func, args);

}

This will result in calling

   ob->func(args).

In combination with the '...' operator, the functionality
of apply() can be implemented:

mixed eval(object ob, string func, mixed >>*<<args)
{

   return funcall(#'call_other, ob, func, args...);

}

will result in calling

   ob->func(args[0],args[1],...,args[sizeof(args)-1]).

Introduced in @subpage driver_mailto:3.2@70 "3.2@70".
Returning a non-closure as it is even when args are given was
introduced with 3.2.1.

   See Also: 
      efun::apply(), efun::quote()
