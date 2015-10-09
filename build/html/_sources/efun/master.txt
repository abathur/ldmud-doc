.. efun:: object master()
  object master(int dont_load)

Returns the master object.

If <dont_load> is false, the function first makes sure that
the master object exists.
If <dont_load> is true, the function just returns the current
master object, or 0 if the current master has been destructed.

.. history
Introduced in LDMud 3.2.10.

  .. seealso:: :master:`master`
