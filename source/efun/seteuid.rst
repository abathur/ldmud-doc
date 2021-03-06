.. efun:: int seteuid(string str)

  Set effective uid to :arg:`str`. The calling object must be privileged to do so by the master object. In most installations it can always be set to the current uid of the object, to the uid of the creator of the object file, or to 0.

  Result is 0 if the euid could not be changed, and non-0 if it was changed.

  When this value is 0, the current object's uid can be changed by :efun:`export_uid`, and only then.

  If strict euid usage is enforced, objects with euid 0 cannot load or clone other objects.

  :history 3.2.1@47 changed: this efun is availabe only when using euids.
  :history 3.2.7 changed: this efun is always available.

  .. seealso:: :efun:`export_uid`, :efun:`getuid`, :efun:`geteuid`, :concept:`native`, :master:`valid_seteuid`
