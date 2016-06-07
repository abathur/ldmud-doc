public class efun {
   /**
    * @synopsis{
    * int call_direct_resolved(mixed result, object ob, string func, ...)
    * }
    * 
   **/
   int call_direct_resolved(mixed result, object ob, string func, ...);
}
Similar to call_direct(). If ob->func() is defined and publicly
accessible, any of the optional extra arguments are passed to
ob->func(...). The result of that function call is stored in
result, which must be passed by reference.

This efun is a twin to call_resolved(), with the difference
being that call_direct_resolved() never calls a default method.

The efun returns 1 if the function could be called.
If ob::fun does not define a publicly accessible function, the
efun will return 0.

ob can also be an object_name. If a string is passed for ob, and
no object with that name does exist, an error occurs.

Introduced in LDMud 3.3.113 with the H_DEFAULT_METHOD hook.

   See Also: 
      efun::call_other(), efun::call_direct(), efun::call_resolved(), applied::create(), @ref driver_LPC_pragma "pragma", efun::extern_call(), efun::function_exists(), `functions`, efun::map_objects()
