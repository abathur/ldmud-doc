.. type:: float
  decimal: <number>.[number]
         : 1.
         : 42.2
  exponential: <number>.<e|E>[+|-]<number>
             : 1.0e3
             : 1.e3
             : 1.e+3
             : 1.e-3
             : 1.0E3
  :title: Floating point numbers
  :topics: type
  :highlighters: (?<=\d)\.
    (?<=\d|\.)(?:[Ee][+-]?)(?=\d)

  A floating point number in the absolute range :macro:`__FLOAT_MIN__` to :macro:`__FLOAT_MAX__` (typically 1e-38 to 1e+38). Floating point numbers are signified by a '.' appearing, e.g. '1' is integer 1, but '1.' is floating-point 1 .

  .. syntax:: float
    decimal: <number>.[number]
      1.
      42.2
    exponential: <number>.<e|E>[+|-]<number>
      1.0e3
      1.e3
      1.e+3
      1.e-3
      1.0E3
    :title: floating point numbers
    :topics: type

  .. todo:: we don't really document that exponential notation is completely valid; needs a syntax def, invalid forms: 1e+13, 1e-13, e13; valid forms: 1.0e3, 1.e3, 1.e4, 1.e+4, 1.e-4
