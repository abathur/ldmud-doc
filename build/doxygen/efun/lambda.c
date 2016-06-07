public class efun {
   /**
    * @synopsis{
    * closure lambda(mixed *arr, mixed)
    * }
    * 
   **/
   closure lambda(mixed *arr, mixed);
}
Constructs a lambda closure, like lambda function in LISP.
The closure is bound to the creating object, and thus can contain
references to global variables.

The first argument is an array describing the arguments
(symbols) passed to the closure upon evaluation by funcall()
or apply().

Introduced in @subpage driver_mailto:3.2@70 "3.2@70".

   See Also: 
      @ref driver_LPC_closures "closures", efun::unbound_lambda(), efun::apply(), efun::funcall(), efun::bind_lambda()
