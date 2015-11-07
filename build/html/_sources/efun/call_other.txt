.. efun:: unknown call_other(object ob, string fun, mixed arg, ...)
  unknown call_other(object *ob, string fun, mixed arg, ...)

  .. note:: In LPC syntax :lang:`->` is an alias for this efun. Because the syntax form is easier to read, :efun:`call_other` is rarely used directly in new code. See the syntax form's documentation for usage notes.

  Call a member function <fun> in another object <ob> with an the argument(s) <arg...>. Result is the value returned from the called function (or 0 for non-existing or void functions).

  Additionally the efun accepts an array of objects as <ob>: the function is called with the same arguments in all the given objects. The single results are collected in an array and yield the final result. Array elements can be objects or the names of existing objects; destructed objects and 0s will yield a '0' as result, but don't cause an error.

  The object(s) can be given directly or via a string (i.e. its object_name). If it is given by a string and the object does not exist yet, it will be loaded.

  If ob::fun does not define a publicly accessible function, the efun will call the H_DEFAULT_METHOD hook if set. If the hook is not set or can't resolve the call either, call_other() will return 0, which is indistinguishable from a function returning 0.

  Calls to the master object never use the H_DEFAULT_METHOD hook. To force non-default calls, the efun call_direct() can be used.

  "publicly accessible" means "public" when calling other objects, and "public" or "static" when calling this_object(). "private" and "protected" function can never be called with call_other().

  The return type of call_other() is 'any' be default. However, if your LPC code uses #pragma strict_types, the return type is 'unknown', and the result of call_other() must be casted to the appropriate type before you can use it for anything.

  .. note:: You may find calls to unlikely functions, especially in older code. For example::

      !Compat: call_other("/users/luser/thing", "???", 0);
       Compat: call_other("users/luser/thing", "???", 0);

    This looks a bit weird but it was used very often to just load the object by calling a non-existing function like "???". Fortunately nowadays there is an efun load_object() for this purpose.

  .. usage::

    First let's do some setup::

      string str, fun;
      fun = "QueryProp";

    Now we'll use these variables with the basic :efun:`call_other`. Both of the following statements call the lfun `QueryProp()` in the current player object with a single argument, P_SHORT::

      str = (string)call_other(this_player(), "QueryProp", P_SHORT);
      str = (string)call_other(this_player(), fun, P_SHORT);

    If you have set #pragma strict_types, you have to do explicit type casting because of the unknown return type.

    You can also pass :efun:`call_other` an array of objects, causing the function to be called for each object. The following statement calls the lfun `short()` in all interactive users and stores the result in an array of strings::

      string *s;
      s = (string *)call_other(users(), "short");

  :history 3.2.8 changed: - a simul_efun call_other() also catches ->() calls.
    - call_other can be applied on arrays of objects.
  :history 3.2.10 change: made the call on arrays of objects configurable.
  :history 3.3.113 changed: the :hook:`H_DEFAULT_METHOD` hook was introduced.
  :history 3.5.0 changed: made the call on arrays of objects non-optional.

  .. seealso:: :lang:`->`, :efun:`call_direct`, :efun:`call_direct_resolved`, :efun:`call_resolved`, :applied:`create`, :lang:`pragma`, :efun:`extern_call`, :efun:`function_exists`, :lang:`functions`, :efun:`map_objects`
