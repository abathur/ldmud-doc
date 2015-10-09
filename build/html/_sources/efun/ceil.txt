.. efun:: float ceil(int|float arg)

Round the <arg>ument upwards the nearest whole number, returning
that value. If the <arg>ument value is an integer, the result will
be that value, converted to float.

EXAMPLES
ceil(4.5)  - returns 5.0
ceil(-4.5) - returns -4.0
ceil(4)    - returns 4.0

.. history
Introduced in LDMud 3.2.7.
LDMud 3.2.9 allowed integers as argument values.

  .. seealso:: :efun:`abs`, :efun:`floor`
