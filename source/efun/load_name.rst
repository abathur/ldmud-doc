.. efun:: string load_name()
  string load_name(object obj)
  string load_name(string obj)

  Return the load name for the object :arg:`obj` which may be given directly or by its name.

  If :arg:`obj` is a clone, return the :efun:`load_name` of :arg:`obj`'s blueprint. If :arg:`obj` is a blueprint, return the filename from which the blueprint was compiled.

  If :arg:`obj` is given by name but not/no longer existing, the function synthesizes the load name as it should be and returns that. If the given name is illegal, the function returns 0.

  As a special case, if :arg:`obj` is 0, the function returns 0.

  For virtual objects this efun returns the original load_name of the object created by the virtual compiler.

  If :arg:`obj` is omitted, the name for the current object is returned.

  In contrast to the :efun:`object_name`, the load name can not be changed by with :efun:`rename_object` or a virtual compiler. However, if an object uses :efun:`replace_program` the load name no longer reflects the actual behaviour of an object.

  The returned name starts with a '/', unless the driver is running in :macro:`__COMPAT_MODE__`.

  .. usage::

    ::

      object o;
      o = clone_object("/std/thing");

      write(load_name(o)); // writes "/std/thing" in !compat mode
                           // and "std/thing"  in compat mode

      write(load_name("/std/thing")); // same as above
      write(load_name("/std/thing#4n5")); // writes 0

  :history 3.2.6 introduced:
  :history 3.2.8 changed: Strings are accepted as arguments
  :history 3.2.9 changed: 0 is accepted as argument

  .. seealso:: :efun:`clone_object`, :efun:`clonep`, :efun:`object_name`, :efun:`load_object`, :efun:`replace_program`, :efun:`program_name`, :efun:`present_clone`
