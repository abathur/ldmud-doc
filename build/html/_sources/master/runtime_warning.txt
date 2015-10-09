.. master:: void runtime_warning(string msg, string curobj, string prog, int line, int inside_catch)

  This function is called to let the mudlib handle a runtime warning,
  e.g. by logging it into a database.

  - <msg> is the warning message.
  - <curobj> is the name of the current object which caused the message
    (the object itself might already be destructed), or 0 if there
    is none.
  - <prog>, <line> determine the name of the program and the line where
    the error occured if the current object exists, otherwise
    they are 0.
  - <inside_catch> : != 0 if the warning occurs inside a catch().

  The driver is limited to three nested warnings, to prevent
  an endless recursion in case runtime_warning() itself causes
  warnings.

  :history 3.3.551 introduced:
  :history 3.3.705 changed: added the <inside_catch> argument.

  .. seealso:: :master:`runtime_error`
