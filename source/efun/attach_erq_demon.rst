.. efun:: int attach_erq_demon(object ob, int do_close)
  int attach_erq_demon(string obname, int do_close)

  This privileged efun is to set/change the connection of the driver to the external erq demon, thus in effect changing the demons.

  The connection of the given interactive :arg:`ob` is taken away from it and stored as the erq-connection. The object itself is then no longer needed, but may stay alive - it is just another non-interactive object then.

  In the second form, the string will be combined as suffix to the filename ERQFILE<obname>, which is then the binary to be forked off as new erq demon. The communication with this erq will take place over unix domain sockets. ERQFILE defaults to BINDIR/erq, where BINDIR is the configuration value for the executable directory.

  .. todo:: not clear how to render ``ERQFILE<obname>``; are these LPC defs? C defs? env vars? Also not super clear what this string should even look like.

  If there is alreay an erq demon connected to the driver, the function will fail unless 'do_close' (default 0) is specified as 1 (or any other odd integer): then the old connection will be closed before attaching the new. The efun returns 1 on success, else 0.

  .. usage::

    To restart the (default) erq, write in :master:`stale_erq`::

      attach_erq_demon("", 0);

  :history 3.2.1@61 introduced:

  .. seealso:: :efun:`send_erq`, :concept:`erq`
