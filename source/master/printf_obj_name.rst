.. master:: string printf_obj_name(object ob)

  Return a printable name for an object. This function is called by :efun:`sprintf` to print a meaningful name in addition to the normal :efun:`object_name`.

  :history 3.2.6 changed: renamed to ``printf_obj_name()`` from ``object_name()`` due to the introduction of :efun:`object_name`.

  .. seealso:: :efun:`sprintf`, :efun:`object_name`
