.. applied:: void exit(object ob)

  This function was used in compat mode drivers in context with moving objects. Nowadays objects are moved by means of the :hook:`move_object` hooks, and use of this lfun is up to the mudlib.

  This function was called in the old environment everytime a living object ob leaves it.

  .. todo:: the following should probably be explained better than it is

  :efun:`this_player` will return a random value, don't use it at this point.

  .. warning:: An error in this function will leave the player stranded in the current room until the next reboot.

  .. seealso:: :applied:`init`
