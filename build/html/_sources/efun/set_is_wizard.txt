.. efun:: int set_is_wizard(object ob, int n)
  :optional:

  Change object ob's wizardhood flag.
  If n is 0, it is cleared, if n is, it is set, if n is -1 the
  current status is reported. The return value is always the old
  value of the flag. Using this function sets a flag in the
  parser, that affects permissions for dumpallobj etc, which are
  by default free for every user.

.. history
  Since 3.2.7 this efun is optional.
