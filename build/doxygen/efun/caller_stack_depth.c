public class efun {
   /**
    * Returns the number of previous objects on the stack. This
    * can be used for security checks.
    * 
    * @synopsis{
    * int caller_stack_depth(void)
    * }
    * 
    * @see efun::caller_stack(), efun::previous_object(), efun::call_other(), efun::call_resolved()
   **/
   int caller_stack_depth(void);
}
