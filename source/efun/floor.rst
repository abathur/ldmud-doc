.. efun:: float floor(float number)

  Round the :arg:`number` downwards the nearest whole number, returning that value. If the :arg:`number` value is an integer, the result will be that value, converted to float.

  .. usage::

    ::

      floor(4.5)  - returns  4.0
      floor(-4.5) - returns -5.0
      floor(5)    - returns  5.0

  :history 3.2.7 introduced:
  :history 3.2.9 changed: adds integers as argument values.

  .. seealso:: :efun:`abs`, :efun:`ceil`
