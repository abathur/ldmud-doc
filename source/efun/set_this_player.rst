.. efun:: void set_this_player(object ob)

  Change the current command giver to :arg:`ob`. :arg:`ob` may be 0 if you want to 'deactivate' the current command giver.

  This efun is not privileged, therefore it should be redefined by a nomask simul_efun which then either completely disables the efun or at least performs some security checks. It is easy to undermine a mudlib's security using this efun.

  :history 3.2.1 introduced:
  :history 3.2.6 changed: added the value 0 as acceptable parameter.

  .. seealso:: :efun:`set_this_object`, :efun:`this_player`
