.. efun:: string getuid(object ob)

  User-ids are not used in compat mode.
  Get user-id of the object, i.e. the name of the wizard or
  domain that is responsible for the object. This name is also
  the name used in the wizlist. If no arg is given, use
  this_object() as default.

  .. history
  :history 3.2.1@47 changed: this creator() is an alias for this efun

  .. seealso:: :efun:`seteuid`, :efun:`geteuid`, :efun:`export_uid`, :efun:`creator`
