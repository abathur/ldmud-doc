.. efun:: string file_name()
  string file_name(object ob)
  :removed:

  Get the name of an object <ob> or, if no argument is given, of
  the current object.

  This name is the name under which the object is stored in the
  muds object table. It is initialised at the creation of the
  object such that blueprints are named after the file they are
  compiled from (without the trailing '.c'), and clones receive
  the name of their blueprint, extended by '#' followed by
  a unique non-negative number. These rules also apply to
  virtual objects - the real name/type of virtual objects
  is ignored.

  The name of an object can be changed with rename_object(), and
  object_name() will reflect any of these changes.

  The returned name always begins with '/' (absolute path),
  except when the parser runs in COMPAT mode.

  .. usage::

    This is guaranteed to be true for all objects ob that are not
    destructed::

      find_object(file_name(ob)) == ob

  :history 3.2.6 changed: renamed to object_name(), this old name is
  available as alias.
  :history 3.2.9 changed: not available if driver is compiled without USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :efun:`clone_object`, :efun:`load_name`, :efun:`load_object`, :efun:`find_object`, :efun:`program_name`, :efun:`rename_object`, :efun:`object_name`
