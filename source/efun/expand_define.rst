.. efun:: string expand_define(string name)
  string expand_define(string name, string arg, ...)

  Expands the macro :arg:`name` with the argument(s) :arg:`arg` ... (default is one empty string ""). Result is the expanded macro, or 0 if there is no macro with that name.

  This efun is applicable only while an object is compiled, therefore its usage is restricted to a few functions like :hook:`H_INCLUDE_DIRS`, or :master:`runtime_error`.

  .. usage::

    While compiling 'foo.c'::

      expand_define("__FILE__") --> "foo.c"

  :history 3.2.1@93 introduced:

  .. seealso:: :overview:`hook`, :master:`runtime_error`
