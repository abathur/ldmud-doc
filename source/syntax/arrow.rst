.. operator:: ->
  call by token: ob->fun (mixed arg, ...)
  call by string: ob->"fun" (mixed arg, ...)
  call by (string) expression/variable: ob->(fun) (mixed arg, ...)
  :name: arrow
  :topics: objects, functions, structs

  .. todo:: need to add use of arrow operator with structs

  The :operator:`arrow` operator (:operator:`->`) is equivalent to :efun:`call_other`. This syntax document discusses how the arrow operator relates to the efun version and gives basic examples; you should see :efun:`call_other` for thorough documentation.

  .. operator:: ->
    ob->fun (mixed arg, ...)
    ob->"fun" (mixed arg, ...)
    ob->(fun) (mixed arg, ...)
    :name: arrow

  ``ob->fun(args)`` and ``ob->"fun"(args)`` are equivalent to ``call_other(ob, "fun", args)``. ``ob->(fun)(args)`` is equivalent to ``call_other(ob, fun, args)`` where fun is a runtime expression returning the function name.

  .. usage::

    This section explores many ways to call ``QueryProp()`` in a player object with a single argument, ``P_SHORT``. First let's do some setup::

      string str, fun;
      fun = "QueryProp";

    Now we'll use these variables with the basic :efun:`call_other`::

      str = (string)call_other(this_player(), "QueryProp", P_SHORT);
      str = (string)call_other(this_player(), fun, P_SHORT);

    And here are three equivalent calls using the arrow syntax form (with the variables from above)::

      str = (string)this_player()->QueryProp(P_SHORT);
      str = (string)this_player()->"QueryProp"(P_SHORT);

      str = (string)this_player()->(fun)(P_SHORT);

    You can also use the arrow form to call a function on each object in an array, so the following statement calls QueryProp in all interactive users and stores the result in an array of strings::

      string *s;
      s = (string *)users()->QueryProp(P_SHORT);

  :history 3.2.8 changed: - the forms ``x->"y"()`` and ``x->(y)()`` are now recognized;
    - the form ``x->y()`` no longer clashes with a local variable also called "y";
    - a simul_efun ``call_other()`` also catches ``->()`` calls.
  :history 3.5.0 changed: split documentation for the arrow ``->`` syntax from documentation for :efun:`call_other`

  .. seealso:: :efun:`call_other`, :efun:`call_direct`, :efun:`call_direct_resolved`, :efun:`call_resolved`, :applied:`create`, :syntax:`pragma`, :efun:`extern_call`, :efun:`function_exists`, :concept:`functions`, :efun:`map_objects`
