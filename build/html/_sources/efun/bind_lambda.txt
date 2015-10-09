.. efun:: closure bind_lambda(closure, object ob)

  Binds an unbound lambda closure to an object and return it.
  The efun can also be used to rebind an efun-, simul-efun
  or operator closure to a different object.

  If the optional argument ob is not this_object(), the privilege
  violation ("bind_lambda", this_object(), ob) occurs.

  :history 3.2@82 introduced:

  .. seealso:: :efun:`lambda`, :efun:`unbound_lambda`, :efun:`apply`, :efun:`funcall`, :lang:`closures`
