.. efun:: float pow(int|float base, int|float exp)

  The function returns the value of :arg:`base` raised to the power of :arg:`exp`.

  .. usage::

    ::

      pow(-2, 3)      // returns -8.0
      pow(8, 1.0/3.0) // returns 2.0

  :history 3.2.7 introduced:
  :history 3.2.9 changed: added integers as arguments.

  .. seealso:: :efun:`exp`, :efun:`log`
