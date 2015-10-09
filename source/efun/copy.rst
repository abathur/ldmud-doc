.. efun:: mixed copy(mixed arg)

  Create a shallow copy of <arg> and return it. For arrays and mappings
  this means that a new array or mapping is created with copies of the
  original content. Embedded arrays and mappings are copied by reference!

  For other values this function is a no-op.

  .. usage::

    mixed *a, *b;

    a = ({ 1, ({ 21, 22 }) });
    b = copy(a);
    a[0] = -1; a[1][0] = -21;
     --> a is now ({ -1, ({ -21, 22 }) })
         b is now ({  1, ({ -21, 22 }) })

  :history 3.2.6 introduced:

  .. seealso:: :efun:`deep_copy`
