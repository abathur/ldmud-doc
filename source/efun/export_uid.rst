.. efun:: void export_uid(object ob)

  Set the uid of object :arg:`ob` to the current object's effective uid. It is only possible when object :arg:`ob` has an effective uid of 0.

  :history 3.2.1@47 changed: this efun is availabe only when using euids.
  :history 3.2.7 changed: this efun is now always available.

  .. seealso:: :efun:`seteuid`, :efun:`getuid`, :efun:`geteuid`, :concept:`uids`, :concept:`native`
