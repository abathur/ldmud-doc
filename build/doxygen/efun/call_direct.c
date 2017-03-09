public class efun {
   /**
    * Call a member function \p fun in another object \p ob with argument(s) \p arg... . Result is the value returned from the called function (or 0 for non-existing or void functions).
    * 
    * This efun is a twin to efun::call_other(), with the difference being that efun::call_direct() never calls a default method.
    * 
    * Additionally the efun accepts an array of objects as \p ob: the function is called with the same arguments in all the given objects. The single results are collected in an array and yield the final result. Array elements can be objects or the names of existing objects; destructed objects and 0s will yield a '0' as result, but don't cause an error.
    * 
    * The object(s) can be given directly or via a string (i.e. its object_name). If it is given by a string and the object does not exist yet, it will be loaded.
    * 
    * `ob->fun(args)` and `"ob_name"->fun(args)` are equivalent to `call_other(ob, "fun", args)`. Nowadays the `ob_name` string can also be a variable.
    * 
    * `ob->fun(args)` and `ob->"fun"(args)` are equivalent to `call_other(ob, "fun", args)`. `ob->(fun)(args)` are equivalent to `call_other(ob, fun, args)` where fun is a runtime expression returning the function name.
    * 
    * If ob::fun does not define a publicly accessible function, the efun::call_other() will return 0, which is indistinguishable from a function returning 0.
    * 
    * "publicly accessible" means "public" when calling other objects, and "public" or "static" when calling `this_object()`. "private" and "protected" function can never be called with efun::call_other().
    * 
    * The return type of efun::call_other() is `any` by default. However, if your LPC code uses @ref driver_syntax_pragma "strict_types", the return is @ref driver_syntax_types "unknown", and the result of efun::call_other() must be casted to the appropriate type before you can use it for anything.
    * 
    * @synopsis{
    * unknown call_direct(object ob, string fun, mixed arg, ...)
    * unknown call_direct(object *ob, string fun, mixed arg, ...)
    * }
    * 
    * @usage{
    * All the following statements call the lfun `QueryProp()` in the current player with the argument `P_SHORT`:
    * 
    * ~~~{.c}
    * string str, fun;
    * 
    * str = (string)call_direct(this_player(), "QueryProp", P_SHORT);
    * fun = "QueryProp";
    * str = (string)call_direct(this_player(), fun, P_SHORT);
    * 
    * You have to do explicit type casting because of the unknown
    * return type, if you have set #pragma strict_types.
    * 
    * // This statement calls the lfun short() in all interactive users
    * // and stores the collected results in a variable.
    * string *s;
    * 
    * s = (string *)call_direct(users(), "short");
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.113) -- with the H_DEFAULT_METHOD.
    * changed (3.2.10) -- made the call on arrays of objects configurable.
    * changed (3.5.0) -- the call on arrays of objects non-optional.
    * }
    * 
    * @see efun::call_other(), efun::call_direct_resolved(), efun::call_resolved(), applied::create(), @ref driver_syntax_pragma "pragma", efun::extern_call(), efun::function_exists(), @ref driver_syntax_functions "functions", efun::map_objects()
   **/
   unknown call_direct(object *ob, string fun, mixed arg, ...);
}
