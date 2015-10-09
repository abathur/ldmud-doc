.. hook:: H_NOTIFY_FAIL

  :arg string value: <msg>
  :arg closure value: string <closure>(string entered_command, object cmd_giver)

  Mandatory hook to issue the default message if an entered
  command couldn't be parsed and no notify_fail() command is in
  effect. Hook setting can be a any closure, or a string.

  If set to a string, it is the message returned to the
  player.

  If set to a closure, it is called with the command and the
  command giver as arguments, and the result is used as failure
  message. Lambda closures are bound to this_player() prior to
  execution.

  <cmd_giver> is the object which received the command in the
  first place. It is usually identical with this_player(),
  unless the H_MODIFY_COMMAND hook changed it.

  :history 3.2.7 changed: added the new 'command_giver' argument.

  .. seealso:: :concept:`hooks`, :hook:`command`, :hook:`modify_command`, :hook:`modify_command_fname`, :hook:`send_notify_fail`
