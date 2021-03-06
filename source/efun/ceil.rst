.. efun:: float ceil(int|float number)

  Round the :arg:`number` upwards the nearest whole number, returning that value. If the :arg:`number` value is an integer, the result will be that value, converted to float.

  .. usage::

    ::

      ceil(4.5)  - returns 5.0
      ceil(-4.5) - returns -4.0
      ceil(4)    - returns 4.0

  :history 3.2.7 introduced:
  :history 3.2.9 changed: allow integers as argument values.

  .. seealso:: :efun:`abs`, :efun:`floor`
