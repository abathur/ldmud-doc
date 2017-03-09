.. applied:: int prevent_insert()
  :deprecated:

  In compat mode, this function is used by :efun:`transfer`.

  Define this function in objects that are neither living nor rooms if you want to prevent to put something into current object.

  Return true if ok, otherwise 0. That means that default is that it is not possible to put something into an object.

  :history 3.3 deprecated: because :efun:`transfer` has been deprecated.

  .. seealso:: :efun:`transfer`, :applied:`can_put_and_get`
