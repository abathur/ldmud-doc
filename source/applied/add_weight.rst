.. applied:: int add_weight(int w)
  :deprecated:

  In compat mode, this function is used by :efun:`transfer`.

  An object that can contain other objects and is not a room must define this function. It is called with the extra weight of the object that is moved into it. If this is ok, then it has to increment the local weight count, and return true. Otherwise, return false, and the new object can not be entered into this object.

  The function is also called with the negative weight in the object that the moving leaves.

  .. note:: no ``set_weight()`` is required by the parser.

  :history 3.3 deprecated: because :efun:`transfer` has been deprecated.

  .. seealso:: :efun:`transfer`, :applied:`query_weight`, :applied:`prevent_insert`
