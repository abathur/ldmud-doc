public class efun {
   /**
    * This is a privileged function, only to be used in the master object or in the simul_efun object.
    * 
    * It changes the result of efun::this_object() in the using function, and the result of efun::previous_object() in functions called in other objects by efun::call_other()/efun::apply()/efun::funcall(). Its effect will remain till there is a return of an external function call, or another call of efun::set_this_object(). While executing code in the master object's program or the primary simul_efun object's program, efun::set_this_object() is granted even if efun::this_object() is altered by efun::set_this_object(). This does not apply to functions inherited from other programs.
    * 
    * Use it with extreme care to avoid inconsistencies. After a call of efun::set_this_object(), some LPC-constructs might behave in an odd manner, or even crash the system. In particular, using global variables or calling local functions (except by call_other) is illegal and actively prevented.
    * 
    * Allowed are efun::call_other(), map functions, access of local variables (which might hold array pointers to a global array), simple arithmetic and the assignment operators.
    * 
    * @par limit: It is currently not possible to directly restore the original current object. So instead of writing:~~~{.c}
    * object me = this_object();
    * set_this_object(that);
    * <some code>
    * set_this_object(me);
    * <more code>
    * 
    * ~~~one has to use a workaround::~~~{.c}
    * private void doit (object that) {
    *   set_this_object(that);
    *   <some code>
    * }
    * 
    * funcall(#'doit, that);
    * <more code>
    * 
    * ~~~Some people would consider this a feature.
    * 
    * @synopsis{
    * void set_this_object(object object_to_pretend_to_be)
    * }
    * 
    * @history{
    * changed (3.2.10) -- actively prevents references to global variables and function calls by address while set_this_object is in effect.
    * }
    * 
    * @see efun::this_object(), efun::set_this_player()
   **/
   void set_this_object(object object_to_pretend_to_be);
}
