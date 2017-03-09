public class efun {
   /**
    * Returns an array of the previous objects who caused the efun::call_other() to efun::this_object(). `previous_object(i)` equals `caller_stack()[i]`.
    * 
    * If you pass the optional argument \p add_interactive (as true value) `this_interactive()` is appended to the array, or 0 if there is no current interactive.
    * 
    * @par note: calls to 'alien lfun closures' (see efun::symbol_function()) generate two entries on the stack if the bound object differs from the closure object: the first is for the bound object, the second for the closure object.
    * 
    * @synopsis{
    * object * caller_stack()
    * object * caller_stack(int add_interactive)
    * }
    * 
    * @usage{
    * interactive object A enters a command which causes a call to a function in object B, that one calls a function in object C and that, in turn, in object D
    * 
    * If D now calls `caller_stack()` the result would be: `({C,B})`. If it calls `caller_stack(1)` the result is: `({C,B,A})`.
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6) -- suggested by Tubmud.
    * }
    * 
    * @see efun::caller_stack_depth(), efun::previous_object(), efun::this_interactive(), efun::call_other()
   **/
   object * caller_stack(int add_interactive);
}
