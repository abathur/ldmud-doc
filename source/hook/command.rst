.. hook:: H_COMMAND

  :arg closure value: int <closure>(string command, object command_giver)
  :arg string value: int <name>(string command, object command_giver)

  Optional hook to parse and execute commands. If this hook is used, it bypasses the normal command parsing done by the driver (including the MODIFY_COMMAND and NOTIFY_FAIL hooks).

  The hook is called with two parameters: the command received from the living (interactive user or NPC), and the living object (the 'command giver') itself. The hook has to return non-0 if the command was found and executed, and 0 otherwise.

  At the time the hook is called, query_command() returns the command string and this_player() returns the living object. query_verb() and query_notify_fail() return 0.

  If the hook is a string, it is the name of an lfun in the command giver; if the hook is a lambda closure, it is bound to the command giver before the call.

  .. history

  .. seealso:: :concept:`hooks`, :hook:`modify_command`, :hook:`modify_command_fname`, :hook:`notify_fail`, :hook:`send_notify_fail`
