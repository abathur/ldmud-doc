.. efun:: object present_clone(string str)
  object present_clone(string str, int n)
  object present_clone(string str, object env)
  object present_clone(string str, object env, int n)
  object present_clone(object obj)
  object present_clone(object obj, int n)
  object present_clone(object obj, object env)
  object present_clone(object obj, object env, int n)
  :experimental:

  This efun searches the inventory of object :arg:`env` (default is ``this_object()``) for an object with a specific blueprint. The blueprint can be specified either by name :arg:`str`, or as the same blueprint as of object :arg:`obj`. The matching criteria in both cases is the ``load_name()``. If :arg:`n` is given, object :arg:`n` in :arg:`env` is returned (if present), otherwise the first object matching :arg:`str` or :arg:`obj`. If no object in :arg:`env` matches the criteria, 0 is returned.

  .. note:: In contrast to :efun:`present`, this efun never searches in the environment of :arg:`env`.

  For plain driver this name starts with a '/', for :macro:`__COMPAT_MODE__` drivers it doesn't.

  .. usage::

    Assume that object :arg:`env` contains the objects ``/obj/money#8``, ``/std/weapon#9``, ``/std/weapon#12`` and ``/obj/key`` in the given order.

    .. todo:: should this table be the way it works everywhere, or translate this table into the comment form I've been using elsewhere?

    ====================================================  ===============
    Function call                                         returns
    ====================================================  ===============
    ``present_clone("/obj/money", env)``                  ``/obj/money#8``
    ``present_clone("/std/weapon#12", env)``              ``/std/weapon#9``
    ``present_clone(find_object("/obj/money#14"), env)``  ``/obj/money#8``
    ``present_clone("/obj/key#18", env)``                 ``/obj/key``
    ``present_clone("/std/weapon#12", env, 2)``           ``/std/weapon#12``
    ``present_clone("/std/weapon#12", env, 3)``           ``0``
    ====================================================  ===============

  :history 3.2.7 introduced:
  :history 3.3.718 changed: added searching for the :arg:`n`th object.

  .. seealso:: :efun:`load_name`, :efun:`present`
