.. efun:: int remove_action(int|string verb)
  int remove_action(int|string verb, object ob)

If <verb> is a string: remove the first action defined by the current
object with the given <verb> from <ob> (default is this_player()).
Return 1 if the action was found and removed, and 0 else.

If <verb> is a number: if non-0, remove all actions defined by
the current object from <ob> (default is this_player()).
Return the number of actions removed.

.. history
Introduced in 3.2.1.
LDMud 3.2.10 added the ability to remove all actions.

  .. seealso:: :efun:`add_action`, :efun:`move_object`
