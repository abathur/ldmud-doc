.. efun:: closure symbol_function(symbol arg)
  closure symbol_function(string arg)
  closure symbol_function(string arg, object|string ob)

  Constructs a lfun closure, efun closure, or operator closure from the first arg (string or symbol). For lfuns, the second arg is the object that the lfun belongs to, specified by the object itself or by its name (the object will be loaded in the second case).

  .. todo:: should there be a clear glossary of closure-related terminology somewhere?

  If the closure is created for an lfun in an object other than the current object, the result is an 'alien lfun closure'. Such closures are bound to the object executing :efun:`symbol_function` (this is what :efun:`to_object` will return), even though the actual code is in that other object (which :efun:`get_type_info` will return).

  Private lfuns can never be accessed this way, static and protected lfuns only if :arg:`ob` is the current object.

  .. usage::

    ::

      symbol_function("efun::users")          // #'users
      symbol_function("QueryProp", other_obj) // other_obj->QueryProp()

  :history 3.2@70 introduced:

  .. seealso:: :efun:`lambda`, :efun:`quote`
