.. efun:: object * clones()
  object * clones(int what)
  object * clones(string|object obj [, int what])

  The efuns returns an array with all clones of a certain blueprint. The array is subject to the usual runtime limits.

  If :arg:`obj` is given, all clones of the blueprint of :arg:`obj` (which may be :arg:`obj` itself) are returned, otherwise all clones of the current object resp. of the current object's blueprint. If :arg:`obj` is given as string, it must name an existing object.

  :arg:`what` selects how to treat clones made from earlier versions of the blueprint:

  ``== 0``
    (default) return the clones of the current blueprint only.

  ``== 1``
    return the clones of the previous blueprints only.

  ``== 2``
    return all clones of the blueprint.

  .. note:: this efun is computationally expensive.

  If the driver is compiled with DYNAMIC_COSTS, the cost of this efun is proportional to the number of objects in the game.

  .. usage::

    ::

      object o, p;
      o = clone_object("/std/thing"); // or "std/thing" in COMPAT mode
      destruct(find_object("/std/thing"));
      p = clone_object("/std/thing");

      clones("/std/thing")    --> returns ({ p })
      clones("/std/thing", 0) --> returns ({ p })
      clones("/std/thing", 1) --> returns ({ o })
      clones("/std/thing", 2) --> returns ({ o, p })

  :history 3.2.8 introduced:
  :history 3.2.9 changed: adds the dynamic cost.

  .. seealso:: :efun:`blueprint`, :efun:`clone_object`, :efun:`clonep`
