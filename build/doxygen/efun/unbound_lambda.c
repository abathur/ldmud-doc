public class efun {
   /**
    * @synopsis{
    * closure unbound_lambda(mixed *args, mixed)
    * }
    * 
   **/
   closure unbound_lambda(mixed *args, mixed);
}
DESCRIPTION
Constructs a lambda closure that is not bound to an object,
like lambda function in LISP.

The closure cannot contain references to global variables, and
all lfun closures are inserted as is, since there is no native
object for this closure. You need to bind it before it can be
called. Ordinary objects can only bind to themselves, binding
to other objects causes a privilege violation(). The point is
that previous_object for calls done from inside the closure
will reflect the object doing bind_lambda(), and all object /
uid based security will also refer to this object.

The first argument is an array describing the arguments
(symbols) passed to the closure upon evaluation by funcall()
or apply(), the second arg forms the code of the closure.

Introduced in @subpage driver_mailto:3.2@82 "3.2@82".

   See Also: 
      @ref driver_LPC_closures "closures", efun::lambda(), efun::apply(), efun::funcall(), efun::bind_lambda()
