.. efun:: unknown call_direct(object ob, string fun, mixed arg, ...)
  unknown call_direct(object *ob, string fun, mixed arg, ...)

  Call a member function :arg:`fun` in another object :arg:`ob` with argument(s) :arg:`arg`... . Result is the value returned from the called function (or 0 for non-existing or void functions).

  This efun is a twin to :efun:`call_other`, with the difference being that :efun:`call_direct` never calls a default method.

  Additionally the efun accepts an array of objects as :arg:`ob`: the function is called with the same arguments in all the given objects. The single results are collected in an array and yield the final result. Array elements can be objects or the names of existing objects; destructed objects and 0s will yield a '0' as result, but don't cause an error.

  The object(s) can be given directly or via a string (i.e. its object_name). If it is given by a string and the object does not exist yet, it will be loaded.

  ``ob->fun(args)`` and ``"ob_name"->fun(args)`` are equivalent to ``call_other(ob, "fun", args)``. Nowadays the ``ob_name`` string can also be a variable.

  ``ob->fun(args)`` and ``ob->"fun"(args)`` are equivalent to ``call_other(ob, "fun", args)``. ``ob->(fun)(args)`` are equivalent to ``call_other(ob, fun, args)`` where fun is a runtime expression returning the function name.

  If ob::fun does not define a publicly accessible function, the :efun:`call_other` will return 0, which is indistinguishable from a function returning 0.

  "publicly accessible" means "public" when calling other objects, and "public" or "static" when calling ``this_object()``. "private" and "protected" function can never be called with :efun:`call_other`.

  The return type of :efun:`call_other` is :type:`any` by default. However, if your LPC code uses :pragma:`strict_types`, the return is :type:`unknown`, and the result of :efun:`call_other` must be casted to the appropriate type before you can use it for anything.

  .. usage::

    All the following statements call the lfun ``QueryProp()`` in the current player with the argument ``P_SHORT``::

      string str, fun;

      str = (string)call_direct(this_player(), "QueryProp", P_SHORT);
      fun = "QueryProp";
      str = (string)call_direct(this_player(), fun, P_SHORT);

      You have to do explicit type casting because of the unknown
      return type, if you have set #pragma strict_types.

      // This statement calls the lfun short() in all interactive users
      // and stores the collected results in a variable.
      string *s;

      s = (string *)call_direct(users(), "short");

  :history 3.3.113 introduced: with the :hook:`H_DEFAULT_METHOD`.
  :history 3.2.10 changed: made the call on arrays of objects configurable.
  :history 3.5.0 changed: the call on arrays of objects non-optional.

  .. seealso:: :efun:`call_other`, :efun:`call_direct_resolved`, :efun:`call_resolved`, :applied:`create`, :syntax:`pragma`, :efun:`extern_call`, :efun:`function_exists`, :syntax:`functions`, :efun:`map_objects`
