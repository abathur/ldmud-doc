.. efun:: string creator(object ob)

  This efun is for backward compatibility only. It is only
  available in compat mode.

  Returns the creator (i.e. the name of the wizard or domain) of
  the object. Default for ob is this_object().

.. history
  Since 3.2.1@47, this efun is an alias for getuid().

  .. seealso:: :efun:`getuid`, :concept:`native`, :concept:`uids`
