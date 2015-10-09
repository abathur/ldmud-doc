.. efun:: int living(object ob)

  Return true if ob is a living object (that is,
  enable_commands() has been called from inside the ob).
  ob may be 0.

  .. usage::

    ``living(this_player())``

  .. seealso:: :efun:`enable_commands`
