.. efun:: int restore_object(string name)
  int restore_object(string str)

  Restore values of variables for current object from the file :arg:`name`, or directly from the string :arg:`str`.

  To restore directly from a string :arg:`str`, the string must begin with the typical line ``#x:y`` as it is created by :efun:`save_object`.

  When restoring from a file, the name may end in ``.c`` which is stripped off by the parser. The master object will probably append a ``.o`` to the :arg:`name`. The validity of the filename is checked with a call to :master:`check_valid_path`.

  .. todo:: There are no other references to check_valid_path; this may be outdated, using the wrong name, or we may be missing the corresponding doc elsewhere. Also, "versions" aren't documented well here.

  Return 1 on success, 0 if there was nothing to restore.

  Variables with :modifer:`nosave` will not be restored::

    ``nosave int xxx;``

  Lfun, variable and simul_efun closures are restored only if they can be found (this excludes closures of private lfuns as well) - if not, they are restored as value ``0``.

  If inheritance is used, then it might be possible that a variable will exist with the same name in more than one place, and thus appear in the  save file multiple times. When restoring, the variables are restored in the order they are found in the inheritance tree. A good practice is to have verbose and unique name on non-static variables, which also will make it more easy to read or patch the save file manually.

  :history 3.2.8 changed: added restoring directly from a string.
  :history 3.2.9 changed: added restoring of non-lambda closures, symbols, and quoted arrays, using a new savefile format version 1.
  :history 3.5.0 changed: added the possibility to restore version 2 with its higher float precision.

  .. seealso:: :efun:`save_object`, :efun:`restore_value`, :master:`valid_read`
