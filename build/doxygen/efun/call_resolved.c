public class efun {
   /**
    * @synopsis{
    * int call_resolved(mixed result, object ob, string func, ...)
    * }
    * 
   **/
   int call_resolved(mixed result, object ob, string func, ...);
}
Similar to call_other(). If ob->func() is defined and publicly
accessible, any of the optional extra arguments are passed to
ob->func(...). The result of that function call is stored in
result, which must be passed by reference.

The efun returns 1 if the function could be called.
If ob::fun does not define a publicly accessible function, the
efun will call the H_DEFAULT_METHOD hook if set. If the hook
is not set or can't resolve the call either, the efun will return 0.
If the hook is set and can resolve the call, the efun will return -1.

Calls to the master object never use the H_DEFAULT_METHOD hook.
To force non-default calls, the efun call_direct_resolved() can
be used.

ob can also be an object_name. If a string is passed for ob
and an object with that name can't be found or loaded, an
error occurs.

LDMud 3.3.113 introduced the H_DEFAULT_METHOD hook.

   See Also: 
      efun::call_other(), efun::call_direct(), efun::call_direct_resolved(), applied::create(), @ref driver_LPC_pragma "pragma", efun::extern_call(), efun::function_exists(), `functions`, efun::map_objects()
