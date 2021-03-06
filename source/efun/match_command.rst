.. efun:: mixed * match_command(string command, object origin)
  :include: <commands.h>

  Take the command :arg:`command`, parse it, and return an array of all matching actions added to :arg:`origin` (read: :arg:`origin` is the object 'issuing' the command).

  Each entry in the result array is itself an array of:

  - string [:macro:`CMDM_VERB`]:   The matched verb.
  - string [:macro:`CMDM_ARG`]:    The argument string remaining, or 0 if none.
  - object [:macro:`CMDM_OBJECT`]: The object defining the action.
  - string [:macro:`CMDM_FUN`]:    The name of the function to call in :macro:`CMDM_OBJECT`, which may be static.

  The efun is useful for both debugging, and for implementing your own :hook:`H_COMMAND` handling.

  :history 3.3.259 introduced:

  .. seealso:: :overview:`hook`, :efun:`execute_command`, :efun:`command`, :efun:`notify_fail`, :efun:`command_stack`
