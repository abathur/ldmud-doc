.. efun:: int set_is_wizard(object ob, int n)
  :optional:

  Change object :arg:`ob's <ob>` wizardhood flag. If :arg:`n` is 0, it is cleared, if :arg:`n` is, it is set, if :arg:`n` is -1 the current status is reported. The return value is always the old value of the flag. Using this function sets a flag in the parser, that affects permissions for dumpallobj etc, which are by default free for every user.

  .. todo:: is my interpretation of the above--that dumpallobj works for any user until you set_is_wizard on at least one user--correct, or is the text wrong?

  :history 3.2.7 changed: made this efun optional.
