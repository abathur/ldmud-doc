.. applied:: int get()
  :deprecated:

  In compat mode, this function is used by :efun:`transfer`.

  If an object wants control over when it is possible to pick it up (i.e. moved into a living object) it must define :applied:`get`, and return 1 if ok to pick up.

  .. note:: `id()` has been called before this to identify the object.

  :history 3.3 deprecated: because :efun:`transfer` has been deprecated.

  .. seealso:: :efun:`transfer`, :applied:`drop`
