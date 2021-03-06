.. efun:: closure unbound_lambda(mixed *args, mixed)

  Constructs a lambda closure that is not bound to an object, like lambda function in LISP.

  The closure cannot contain references to global variables, and all lfun closures are inserted as is, since there is no native object for this closure. You need to bind it before it can be called. Ordinary objects can only bind to themselves, binding to other objects causes a privilege violation. The point is that previous_object for calls done from inside the closure will reflect the object doing :efun:`bind_lambda`, and all object / uid based security will also refer to this object.

  .. todo:: privilege violation above

  The first argument is an array describing the arguments (symbols) passed to the closure upon evaluation by :efun:`funcall` or :efun:`apply`, the second arg forms the code of the closure.

  :history 3.2@82 introduced:

  .. seealso:: :type:`closure`, :efun:`lambda`, :efun:`apply`, :efun:`funcall`, :efun:`bind_lambda`
