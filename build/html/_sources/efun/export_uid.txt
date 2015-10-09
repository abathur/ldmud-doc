.. efun:: void export_uid(object ob)

  Set the uid of object ob to the current object's effective uid.
  It is only possible when object ob has an effective uid of 0.

.. history
  Since 3.2.1@47, this efun is availabe only when using euids.
  Since 3.2.7, this efun is always available.

  .. seealso:: :efun:`seteuid`, :efun:`getuid`, :efun:`geteuid`, :concept:`uids`, :concept:`native`
