.. efun:: void set_extra_wizinfo(object wiz, mixed extra)
  void set_extra_wizinfo(string wiz, mixed extra)
  void set_extra_wizinfo(int    wiz, mixed extra)

Set the value <extra> as the 'extra' information for the wizlist
entry of <wiz>.

If <wiz> is an object, the entry of its creator (uid) is used.
If <wiz> is a string (a creator aka uid), it names the entry
to use.
If <wiz> is the number 0, the data is set in the default wizlist
entry. It can be used to store data for the lifetime of this
driver run, like the time of the last reboot.

The <extra> argument may be any value.

The function causes a privilege violation.

  .. seealso:: :efun:`get_extra_wizinfo`, :efun:`set_extra_wizinfo_size`, :efun:`wizlist_info`