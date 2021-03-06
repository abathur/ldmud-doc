.. efun:: int call_resolved(mixed result, object ob, string func, ...)

  Similar to :efun:`call_other`. If ``ob->func()`` is defined and publicly accessible, any of the optional extra arguments are passed to ``ob->func(...)``. The result of that function call is stored in result, which must be passed by reference.

  The efun returns 1 if the function could be called. If ob::fun does not define a publicly accessible function, the efun will call the :hook:`H_DEFAULT_METHOD` hook if set. If the hook is not set or can't resolve the call either, the efun will return 0. If the hook is set and can resolve the call, the efun will return -1.

  Calls to the master object never use the :hook:`H_DEFAULT_METHOD` hook. To force non-default calls, :efun:`call_direct_resolved` can be used.

  ob can also be an object_name. If a string is passed for ob and an object with that name can't be found or loaded, an error occurs.

  :history 3.3.113 changed: added the :hook:`H_DEFAULT_METHOD` hook.

  .. seealso:: :efun:`call_other`, :efun:`call_direct`, :efun:`call_direct_resolved`, :applied:`create`, :syntax:`pragma`, :efun:`extern_call`, :efun:`function_exists`, :syntax:`functions`, :efun:`map_objects`
