.. efun:: float to_float(int)
  float to_float(string)
  float to_float(float)
  (float)<value>

DESCRIPTION
Ints are expanded to floats; strings are converted up to the
first character that doesnt belong into a float.

Floats are just returned.

BUGS
The cast notation only works if the precise type of <value>
is known at compile-time. This will not be fixed - use the
function form instead.

  .. seealso:: :efun:`to_string`, :efun:`to_int`, :efun:`sscanf`
