.. efun:: object * deep_inventory(void)
  object * deep_inventory(object ob)
  object * deep_inventory(object ob, int depth)

  Returns an array of the objects contained in the inventory of :arg:`ob` (or ``this_object()`` if no arg given) and in the inventories of these objects, climbing down recursively.

  If :arg:`depth` is given and not 0, the result is limited as follows:

  :arg:`depth` > 0
    Only the objects in the first :arg:`depth` levels of inventory are returned.

  :arg:`depth` < 0
    Only the objects in level :arg:`-depth <depth>` of inventory are returned.

  In this, level '1' is the inventory of :arg:`ob` itself.

  .. usage::

    Consider the following nested inventory structure:

    - ob

      - ob1
      - ob2

        - ob21

      - ob3

        - ob31

      - ob4

    Given this structure, :efun:`deep_inventory` would return::

      deep_inventory(ob)     // ({ob1, ob2, ob3, ob4, ob21, ob31})
      deep_inventory(ob, 1)  // ({ob1, ob2, ob3, ob4})
      deep_inventory(ob, 2)  // ({ob1, ob2, ob3, ob4, ob21, ob31})
      deep_inventory(ob, -2) // ({ob21, ob31})

  :history 3.3.554 changed: added the :arg:`depth` parameter

  .. seealso:: :efun:`first_inventory`, :efun:`next_inventory`, :efun:`all_inventory`
