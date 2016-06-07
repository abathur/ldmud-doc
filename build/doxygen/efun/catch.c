public class efun {
   /**
    * Evaluate the expressions. If there is no error, 0 is returned.
    * If there is an error, the evaluation of the expressions stops at
    * that point, and a string with the error message is returned.
    * 
    * System error messages start with a leading '*', user-defined
    * error values (other than 0) as given to throw() and raise_error() are
    * returned as they are.
    * 
    * If at the time the catch() is encountered less than
    * __CATCH_EVAL_COST__ eval ticks are left, a runtime error will be
    * thrown from inside the catch() (and thus caught like every other
    * error) and the expressions will not be executed. The 'reserve'
    * modifier can be used to reserve a different amount of eval ticks.
    * 
    * The default behaviour of catch() can be changed using modifiers:
    * 
    * 'nolog':   Normally, the caught error will be logged in the
    *    error logs for easier debugging. With this
    *    modifier, the log is suppressed.
    *    
    * 'publish': Normally, master::runtime_error() is not called
    *    for a caught error. This modifier instructs
    *    catch() to call it nevertheless.
    *    
    * 'reserve <expr>': The expression has to evaluate to a number
    *    greater than 0 and is used to determine the amount
    *    of eval ticks to reserve, instead of the default
    *    of __CATCH_EVAL_COST__. The minimum required
    *    are 2 * __MASTER_EVAL_COST__.
    *    
    * catch() itself is not expensive as far as execution time is
    * concerned: it is about the same as a intra-object function call.
    * 
    * throw() is not very expensive either, but does include the
    * internal cleanup of several structures.
    * 
    * Real runtime errors on the other hand are expensive regardless
    * of whether they are caught or not, as they include the generation
    * of the stack backtrace.
    * 
    * catch() is not really an efun but a compiler directive.
    * 
    * @synopsis{
    * mixed catch(expr, expr, ...)
    * mixed catch(expr, expr, ... ; modifiers)
    * }
    * 
    * @usage{
    * object obj;
    * string err;
    * if (err = catch(obj = clone_object("/foo/bar/baz")))
    * write("Cannot clone object, reason:"+err"+n");
    * }
    * 
   **/
   mixed catch(expr, expr, ... ; modifiers);
}
