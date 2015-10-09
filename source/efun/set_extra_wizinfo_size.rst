.. efun:: void set_extra_wizinfo_size(int)

  Indicate that the wizlist should contain an array of this size
  with extra info foreach wizard. A negative value indicates
  a non-array value.

  Causes a privilege violation.

  The value is only used to allocate a proper empty 'extra' value
  for newly created wizlist entries.

  .. seealso:: :efun:`get_extra_wizinfo`, :efun:`set_extra_wizinfo`, :efun:`wizlist_info`
