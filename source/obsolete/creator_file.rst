.. master:: string creator_file(mixed ob)
  :removed:

  Return the name of the creator of a newly created object, i.e.
  the name of the user that is responsible for the LPC source
  file the object was loaded from. If the function returns 0,
  the object can't be loaded and is destructed again
  immediately.

  In !compat mode, the returned string serves as the initial uid
  (``cuid'') of the object. Objects whose cuid is the
  backbone-id will then get the uid of the currently active user
  as their userid instead.

  Under compat mode this function is called as well and provides
  the information returned by the creator() efun.

  If this function is not provided by the master object, no
  other object can be loaded.

  :history 3.2.1 removed: replaced by the _UID driver hooks.

  .. seealso:: :concept:`uids`, :efun:`creator`, :efun:`getuid`
