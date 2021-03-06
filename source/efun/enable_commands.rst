.. efun:: void enable_commands()

  Enable this object to use commands normally accessible to users. This also marks the current object as "living".

  Avoid calling this function outside of ``create()`` (or ``reset(0)`` in compat mode), because the command giver will be set to this object.

  .. usage::

    This example makes the current object a living object which then can be accessed via ``find_living("dummymonster")``::

      void create() {
        enable_commands();
        set_living_name("dummymonster");
      }

  .. seealso:: :efun:`command`, :efun:`living`, :efun:`disable_commands`, :concept:`native`, :overview:`hook`
