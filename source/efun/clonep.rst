.. efun:: int clonep()
  int clonep(object obj)
  int clonep(string obj)
  int clonep(mixed  arg)

  The efun returns 1 if :arg:`obj` is a clone, and 0 if it is not. The :arg:`obj` can be given as the object itself, or by its name. If :arg:`obj` is omitted, the current object is tested. Arguments of other types return 0. Objects with replaced programs no longer count as clones.

  .. usage::

    ::

      object o;
      o = clone_object("/std/thing");
      write(clonep(o));                           --> writes "1"
      write(clonep("/std/thing"))                 --> writes "0"

      (In COMPAT_MODE use "std/thing" as the filename)

  :history 3.2.6 introduced:
  :history 3.2.7 changed: objects with replaced programs no longer count as clones.

  .. seealso:: :efun:`load_name`, :efun:`clone_object`, :efun:`clones`, :efun:`closurep`, :efun:`floatp`, :efun:`mappingp`, :efun:`objectp`, :efun:`intp`, :efun:`referencep`, :efun:`pointerp`, :efun:`stringp`, :efun:`symbolp`, :efun:`structp`
