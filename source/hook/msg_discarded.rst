.. hook:: H_MSG_DISCARDED

  :arg string value: <msg>
  :arg closure value: string <closure>(object user)

  Optional hook to specify a message or take other measures when a message had to be discarded, because they could not be delivered to the player <user>. If the hook is not set, a standard message is used.

  If the hook is a string, this text will be sent as soon as possible to the player informing about the lost transmission.

  If the hook is a closure, it is the function to be called and the result is used as the message to be sent. Lambda closures are bound to the interactive <user> first.

  :history 3.3.719 introduced:

  .. seealso:: :overview:`hook`, :efun:`configure_interactive`
