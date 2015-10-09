.. efun:: mixed query_notify_fail()
  mixed query_notify_fail(int flag)

If <flag> is not given or 0: return the string or closure which
was last set as error message for this command (with notify_fail()).

If <flag> is given and 1: return the object which issued the last
notify_fail().

If nothing was set yet, return 0.

.. history
Introduced in LDMud 3.2.7.
LDMud 3.2.8 added the <flag> parameter.

  .. seealso:: :efun:`add_action`, :efun:`query_verb`, :efun:`query_command`, :efun:`notify_fail`,
 :concept:`hooks`
