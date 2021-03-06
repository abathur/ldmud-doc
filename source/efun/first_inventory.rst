.. efun:: object first_inventory()
  object first_inventory(string ob)
  object first_inventory(object ob)

  Get the first object in the inventory of :arg:`ob`, where :arg:`ob` is either an object or the file name of an object. If :arg:`ob` is not given, the current object is assumed.

  .. usage::

    This efun is mostly used in the following context::

      for(object ob = first_inventory(container); ob; ob = next_inventory(ob)) {
        <some actions>
      }

    If you use such calls frequently then it would be very useful to use a preprocessor macro::

      #define FORALL(x, y) for(x=first_inventory(y);x;x=next_inventory(x))

    So the above example could be written like this::

      FORALL(ob, container) {
        <some actions>
      }

    .. warning:: If the object ob is moved inside <some actions>, then :efun:`next_inventory` will return an object from the new inventory of ob. You also shouldn't call :efun:`next_inventory` on destructed objects.

      In case of move and/or destruction the following is a better solution::

        for(object ob = first_inventory(container); ob;) {
          object next = next_inventory(ob);
          <some actions and moves and/or removes>
          ob = next;
        }

  .. seealso:: :efun:`next_inventory`, :efun:`all_inventory`, :efun:`environment`, :efun:`deep_inventory`
