.. master:: string *define_include_dirs(void)
  :removed:

  Return an array of string patterns giving the absolut paths
  where to search an include file. The patterns have to have a
  %s at the place where the name given in the #include statement
  has to be inserted.

  .. usage::

    ``define_include_dirs() { return ({ "sys/%s", "lib/%s" }); }``

  :history 3.2.1 removed: replaced by H_INCLUDE_DIRS hook.

  .. seealso:: :master:`master`
