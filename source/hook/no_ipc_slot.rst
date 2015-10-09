.. hook:: H_NO_IPC_SLOT

  :arg int value: 0
  :arg string value: <msg>

  Optional hook specifying the message given to logins
  rejected due to space limitations (MAX_PLAYER).
  Hook setting has to be string.

  If set to 0, the default message "Lpmud is full. Come back
  later." is issued.

  .. history

  .. seealso:: :concept:`hooks`
