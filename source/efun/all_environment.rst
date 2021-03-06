.. efun:: object * all_environment()
  object * all_environment(object obj)

  Returns an array with all environments object :arg:`obj` is in. If :arg:`obj` is omitted, the environments of the current object is returned.

  If :arg:`obj` has no environment, or if :arg:`obj` is destructed, 0 is returned.

  .. usage::

    If :arg:`obj` is a match in a matchbox which is in a box in a chest, in a room, ``all_environment(obj)`` will return ``({ matchbox, box, chest, room })``.

  :history 3.2.6 introduced: suggested by Tubmud.

  .. seealso:: :efun:`environment`, :efun:`all_inventory`
