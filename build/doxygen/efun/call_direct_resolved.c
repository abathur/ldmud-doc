public class efun {
   /**
    * Similar to efun::call_direct(). If `ob->func()` is defined and publicly accessible, any of the optional extra arguments are passed to `ob->func(...)`. The result of that function call is stored in result, which must be passed by reference.
    * 
    * This efun is a twin to efun::call_resolved(), with the difference being that efun::call_direct_resolved() never calls a default method.
    * 
    * The efun returns 1 if the function could be called. If ob::fun does not define a publicly accessible function, the efun will return 0.
    * 
    * ob can also be an object_name. If a string is passed for ob, and no object with that name does exist, an error occurs.
    * 
    * @synopsis{
    * int call_direct_resolved(mixed result, object ob, string func, ...)
    * }
    * 
    * @history{
    * introduced (3.3.113) -- with the H_DEFAULT_METHOD.
    * }
    * 
    * @see efun::call_other(), efun::call_direct(), efun::call_resolved(), applied::create(), @ref driver_syntax_pragma "pragma", efun::extern_call(), efun::function_exists(), @ref driver_syntax_functions "functions", efun::map_objects()
   **/
   int call_direct_resolved(mixed result, object ob, string func, ...);
}
