public class efun {
   /**
    * @synopsis{
    * int remove_call_out(string fun)
    * int remove_call_out(closure fun)
    * }
    * 
   **/
   int remove_call_out(closure fun);
}
Remove next pending call-out for function <fun> in the current
object, resp. the next pending call-out for closure <fun>.
The time left is returned.

-1 is returned if there were no call-outs pending to this
function.

EXAMPLES
To remove every pending call-out to MyTimer() :

while (remove_call_out("MyTimer") != -1) /* continue >>*<</ ;

Removing a call_out to a closure was introduced in @subpage driver_mailto:3.2.1@45 "3.2.1@45".

   See Also: 
      efun::call_out(), efun::call_out_info(), efun::find_call_out()
