.. efun:: int remove_action(int|string verb)
  int remove_action(int|string verb, object ob)

  If :arg:`verb` is a string: remove the first action defined by the current object with the given :arg:`verb` from :arg:`ob` (default is ``this_player()``). Return 1 if the action was found and removed, and 0 else.

  If :arg:`verb` is a number: if non-0, remove all actions defined by the current object from :arg:`ob` (default is ``this_player()``). Return the number of actions removed.

  :history 3.2.1 introduced:
  :history 3.2.10 changed: added the ability to remove all actions.

  .. seealso:: :efun:`add_action`, :efun:`move_object`
