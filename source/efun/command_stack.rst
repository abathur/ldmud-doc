.. efun:: mixed * command_stack(void)
  :include: <commands.h>

  Return an array describing the current command stack. The array has
  command_stack_depth() entries, the first describing the top-level
  command, and the last describing the current one.

  Each entry is an array itself with these entries:

    string [CMD_VERB]:    the verb of this command
    string [CMD_TEXT]:    the full command text
    object [CMD_ORIGIN]:  the original command giver
    object [CMD_PLAYER]:  the current command giver
    mixed  [CMD_FAIL]:    the notify_fail setting (or 0).
    mixed  [CMD_FAILOBJ]: the object which set the notify_fail setting.

  CMD_ORIGIN and CMD_PLAYER are usually the same; there is a difference
  only if the modify_command hook changes the command giver with
  set_this_player().

  .. note:: any of the entries may be returned as 0.

.. history
  :history 3.2.7 introduced:
  :history 3.2.8 changed: added the CMD_FAILOBJ result

  .. seealso:: :efun:`command`, :efun:`command_stack_depth`, :efun:`notify_fail`
