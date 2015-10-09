.. efun:: void ed()
void ed(string file)
void ed(string file, string func)

Calling without arguments will start the editor ed with the
name of the error file, that was returned by
master->valid_read(0, geteuid(this_player()), "ed_start",
this_player()), usually something like ~/.err. If that file is
empty, ed will immediatly exit again.
Calling ed() with argument file will start the editor on the
file. If the optional argument func is given, this function
will be called after exiting the editor.

The editor ed is almost ed(1) compatible.

  .. seealso:: :efun:`enable_commands`, :efun:`query_editing`, :lang:`ed0`
