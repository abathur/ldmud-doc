public class efun {
   /**
    * Remove next pending call-out for function \p fun in the current object, resp. the next pending call-out for closure \p fun. The time left is returned.
    * 
    * -1 is returned if there were no call-outs pending to this function.
    * 
    * @synopsis{
    * int remove_call_out(string fun)
    * int remove_call_out(closure fun)
    * }
    * 
    * @usage{
    * To remove every pending call-out to `MyTimer()`:
    * 
    * ~~~{.c}
    * while (remove_call_out("MyTimer") != -1) continue;
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.1) -- can now remove a call_out to a closure
    * }
    * 
    * @see efun::call_out(), efun::call_out_info(), efun::find_call_out()
   **/
   int remove_call_out(closure fun);
}
