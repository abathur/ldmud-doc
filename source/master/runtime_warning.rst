.. master:: void runtime_warning(string msg, string curobj, string prog, int line, int inside_catch)

  This function is called to let the mudlib handle a runtime warning, e.g. by logging it to a database.

  - :arg:`msg` is the warning message.
  - :arg:`curobj` is the name of the current object which caused the message (the object itself might already be destructed), or 0 if there is none.
  - :arg:`prog`, :arg:`line` determine the name of the program and the line where the error occured if the current object exists, otherwise they are 0.
  - :arg:`inside_catch` : != 0 if the warning occurs inside a :efun:`catch`.

  .. limit:: The driver is limited to three nested warnings, to prevent an endless recursion in case :master:`runtime_warning` itself causes warnings.

  :history 3.3.551 introduced:
  :history 3.3.705 changed: added the :arg:`inside_catch` argument.

  .. seealso:: :master:`runtime_error`
