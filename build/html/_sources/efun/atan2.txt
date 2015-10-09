.. efun:: float atan2(int|float y, int|float x)

  Returns the angle part of the polar coordinates of the point (x, y)
  in the range (-pi, pi].

  Note the exchange of the coordinates x and y in the parameter list
  reflecting the sequenz in the gradient to angle transformation
  atan(y / x).

  :history 3.2.9 changed: added integers as arguments

  .. seealso:: :efun:`sin`, :efun:`cos`, :efun:`tan`, :efun:`asin`, :efun:`acos`, :efun:`atan`
