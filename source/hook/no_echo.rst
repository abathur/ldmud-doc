.. hook:: H_NOECHO

  .. todo:: this was formerly documenting :macro:`H_TELNET_NEG`, which I think was probably a mistake, though I'm not 100% sure; needs to be clarified.

  :arg string value: void <name>(int flag, object user, int no_telnet)
  :arg closure value: void <closure>(int flag, object user, int no_telnet)

  Optional hook to specifiy how to perform the telnet actions to switch the echo mode (used for e.g. passwords with :efun:`input_to`). Hook setting may be any closure or a string. If not set, a default handling is performed.

  If the setting is a string, it is used as name of an lfun to call in the interactive <user>, where <flag> is the echo-flag passed to the :efun:`input_to`statement.

  If the setting is a closure, it is called with the same arguments, and unbound lambda-closures being bound to ``this_player()`` prior to execution.

  .. todo:: not clear what <local> in the next paragraph refers to

  <local> is a boolean flag: it is TRUE when :efun:`input_to` was called with the :macro:`INPUT_NO_TELNET` flag.

  When set, the hook is called whenever the driver needs to change the echo mode, thus you can negotiate about things that are coupled with it, like LINEMODE or character-at-a-time.

  .. warning:: If this hook is used, the control of all telnet negotiation is transferred to the mudlib: all incoming negotiations are passed to :hook:`H_TELNET_NEG`, and the sending of no-echo negotiations is handled by this hook.

  :history 3.2.11/3.3.593 changed: added the <no_telnet> argument.

  .. seealso:: :overview:`hook`, :concept:`telnet`, :hook:`telnet_neg`
