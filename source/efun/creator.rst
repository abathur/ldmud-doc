.. efun:: string creator(object ob)

  This efun is for backward compatibility only. It is only available in compat mode.

  Returns the creator (i.e. the name of the wizard or domain) of the object. Default for :arg:`ob` is ``this_object()``.

  :history 3.2.1@47 changed: this efun is now an alias for :efun:`getuid`.

  .. seealso:: :efun:`getuid`, :concept:`native`, :concept:`uids`
