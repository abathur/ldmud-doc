public class efun {
   /**
    * @synopsis{
    * void call_out(string fun, int delay, mixed arg, ...)
    * void call_out(closure cl, int delay, mixed arg, ...)
    * }
    * 
   **/
   void call_out(closure cl, int delay, mixed arg, ...);
}
Set up a call to function fun in the current object, or to
closure cl. The call will take place after <delay> seconds, with the
remaining argument list provided.
<delay> can be a minimum time of 0 (negative values are implicitly
treated as 0), but the real delay will be something between <delay>
and <delay> + __ALARM_TIME__.

call_out() saves and restores the current user. It is now
possible to use say() or write() which rely on a current
user to be something useful.

call_out() can only call functions by name <fun> which are publicly
accessible, i.e. "public" and "static" functions. "private" and
"protected" functions can't be called.

If <fun> does not define a publicly accessible function, the
efun will call the H_DEFAULT_METHOD hook if set.
Calls to the master object never use the H_DEFAULT_METHOD hook.

The execution of the call_out()s implies a simple (not
exhaustive) measure against rabbits: the evaluation costs of
those call_outs() executing at the same time are summed up on
a per-UID base. If the summed-up costs exceed the given maximum,
a 'too long evaluation' error will occur and any remaining
call_outs() of this user scheduled for the same time are
discarded.

If two call_out()s were started with the same target time
the one that was issued first will be executed first.

EXAMPLES
call_out("RefreshMe", 10);

This will call the function RefreshMe() in 10 seconds without
any arguments. The function RefreshMe() can then call out
itself again which will result in a loop (not in a recursion)
which can be used to check or set up things in the object in
intervals. Be aware that callouts are stored in a linear
list, and so are somewhat expensive for the driver.

And YES: self-replicating call_out()s, where each call_out()
creates two or more other call_out()s in a loop (so called
'rabbits') slow the mud down very fast, and are even able
to crash it. No need to try it yourself.

      See Also: 
         efun::remove_call_out(), efun::call_out_info(), efun::find_call_out(),

   efun::this_player(), applied::reset(), applied::heart_beat()
