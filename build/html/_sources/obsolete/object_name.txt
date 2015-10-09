.. master:: string object_name(object ob)
  :removed:

  Return a printable name for an object. This function is called
  by sprintf() to print a meaningful name in addition to the
  normal object_name().

  :history 3.2.6 changed: renamed to printf_obj_name() due to the introduction
    of an efun with this name.

  .. seealso:: :efun:`sprintf`, :master:`printf_obj_name`, :efun:`object_name`
