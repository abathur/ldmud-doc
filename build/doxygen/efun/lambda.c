public class efun {
   /**
    * Constructs a lambda closure, like lambda function in LISP. The closure is bound to the creating object, and thus can contain references to global variables.
    * 
    * The first argument is an array describing the arguments (symbols) passed to the closure upon evaluation by efun::funcall() or efun::apply().
    * 
    * @synopsis{
    * closure lambda(mixed *arr, mixed)
    * }
    * 
    * @history{
    * introduced (3.2@70)
    * }
    * 
    * @see @ref driver_syntax_closures "closure", efun::unbound_lambda(), efun::apply(), efun::funcall(), efun::bind_lambda()
   **/
   closure lambda(mixed *arr, mixed);
}
