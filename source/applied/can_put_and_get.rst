.. applied:: int can_put_and_get()
  :deprecated:

  In compat mode, this function is used by the efun transfer().

  Define this function in objects that are neither living nor
  rooms if you want to make it possible to put something into
  current object.

  Return true if ok, otherwise 0. That means that default is
  that it is not possible to put something into an object.

  .. history
  :history 3.3 deprecated: because transfer() has been deprecated.

  .. seealso:: :efun:`transfer`, :applied:`prevent_insert`

