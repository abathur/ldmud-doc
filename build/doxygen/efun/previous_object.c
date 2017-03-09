public class efun {
   /**
    * Returns an object pointer to the object that did a call (efun::call_other(), efun::funcall(), etc) to the current object, if any. If that object is destructed, the function returns 0.
    * 
    * If the optional \p i is given and `0 <= i < caller_stack_depth()`, the call_others are followed back \p i times (i.e. `previous_object(1)` returns the caller of the caller). If \p i is less than 0, the first previous object is returned (as if `i == 0` was passed).
    * 
    * There is an important special case: in functions called by the gamedriver in reaction to some external event (e.g. commands added by add_action), `previous_object()` will return `this_object()`, but `previous_object(0)` will return 0.
    * 
    * See Also: 
    *    efun::call_other(), efun::this_object(), efun::this_player(),
    *    
    * efun::caller_stack(), efun::caller_stack_depth(), efun::extern_call()
    * 
    * @synopsis{
    * object previous_object()
    * object previous_object(int i)
    * }
    * 
    * @usage{
    * This example shows how we can check if the last call to a function of the current object is secure or if we should abort execution:
    * 
    * ~~~{.c}
    * int security() {
    *    object prev;
    *    if (!(prev=previous_object()));
    *    else if (getuid(prev)  != getuid(this_object()));
    *    else if (geteuid(prev) != geteuid(this_object()));
    *    else return 1;
    *    return 0;
    * }
    * void highly_sensible_func() {
    *     if (!security())
    *         return;
    *     ...
    * }
    * 
    * ~~~
    * 
    * }
    * 
   **/
   object previous_object(int i);
}
