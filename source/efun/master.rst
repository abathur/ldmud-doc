.. efun:: object master()
  object master(int dont_load)

  Returns the master object.

  If :arg:`dont_load` is false, the function first makes sure that the master object exists.

  If :arg:`dont_load` is true, the function just returns the current master object, or 0 if the current master has been destructed.

  :history 3.2.10 introduced:

  .. seealso:: :master:`overview`
