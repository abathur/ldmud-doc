.. efun:: object present(string str)
  object present(string str, int n)
  object present(string str, object env)
  object present(string str, int n, object env)
  object present(object ob)
  object present(object ob, object env)

  This efun checks if an object is present in a given environment. The object is identified by id :arg:`str` or by an object :arg:`ob`. This latter form of the efun can be used as a fast way to test for the presence of a known object.

  When searching objects by id, the efun by default returns the first object found matching the id. In order to search for other than the first object, a number can be specified either directly as the argument :arg:`n`, or implicetely inside the :arg:`str` in the form ":arg:`id` :arg:`n`".

  By default, the efun searches first in the inventory of ``this_object()``, then in its environment. However, if :arg:`env` is given, the efun searches just inside :arg:`env`.

  When searching both inventory and environment of :efun:`this_object`, the numbering is applied linear over both spaces (see examples).

  The driver identifies objects by calling :applied:`id` in each object.

  .. usage::

    Find the first 'chest' object within the calling object::

      present("chest");

    Find the second 'chest' object within the calling object::

      present("chest 2")

    Find the first 'chest 2' object within the calling object::

      present("chest 2", 1)

    Assuming there is one "chest" inside the current object, and two in its environment::

      present("chest", 1) // returns the chest inside
      present("chest", 2) // returns the first chest outside
      present("chest", 3) // returns the second chest outside

    A typical 2.4.5-implementation of the :samp:`do {id} {n}` command style is::

      void init() { add_action("open_chest", "open"); }

      int open_chest (string str) {
        if (present (str) != this_object ())
            return 0; // Not this chest
        ...
      }

  :history 3.2.11/3.3.610 changed: introduced the ``(str, n)`` argument form.
  :history 3.3.713 changed: modified the :arg:`n` search behaviour so that the numbering is applied over both inventory and environment together. Before, the numbering was individual in each space, leading to situations where low-numbered objects in the environment were hidden by those in the inventory.

  .. seealso:: :efun:`move_object`, :efun:`environment`, :efun:`this_object`, :efun:`present_clone`, :applied:`id`, :applied:`init`
