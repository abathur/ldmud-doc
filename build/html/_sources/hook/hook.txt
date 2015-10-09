.. concept:: hooks
  :synopsis: Supported driver hooks.
  :topic: driver

  To allow a greater flexibility of the muds, the gamedrivers
  since 3.2.1 moved several once hardcoded 'underground'
  activities from the driver into the mudlib. This includes for
  example the differences between compat and native mode.

  The hooks are set with the privileged efun set_driver_hook().
  Some of the hooks are mandatory, some not. Most hooks accept
  unbound lambda closures as values, some also lfun closures or
  even strings.

  The hooks are identified by an ordinal number, for which
  symbolic names are defined in :file:`/sys/driverhooks.h`.

  .. glossary::
    :hook:`H_MOVE_OBJECT0`
    :hook:`H_MOVE_OBJECT1`
      Mandatory hooks to implement the efun void move_object().


    :hook:`H_LOAD_UIDS`
    :hook:`H_CLONE_UIDS`
      Mandatory hooks to determine the uid and euid of loaded or cloned
      objects.


    :hook:`H_CREATE_SUPER`
    :hook:`H_CREATE_OB`
    :hook:`H_CREATE_CLONE`
      Optional hooks to initialize an object after creation.

      :hook:`H_CREATE_SUPER` is called for blueprints implicitely loaded
      by inheritance, :hook:`H_CREATE_OB` for explicitely loaded
      blueprints/objects, and :hook:`H_CREATE_CLONE` for cloned objects.


    :hook:`H_RESET`
      Optional hook to reset an object.


    :hook:`H_CLEAN_UP`
      Optional hook to clean up an object.


    :hook:`H_DEFAULT_METHOD`
      Optional hook to provide default implementation for unresolved
      calls.


    :hook:`H_DEFAULT_PROMPT`
      Optional hook for the command prompt. If this hook is not used,
      the driver will use "> " as the command prompt.


    :hook:`H_PRINT_PROMPT`
      Optional hook to print the current command prompt. If this hook is
      not set, the driver will just print the prompt to the user.


    :hook:`H_COMMAND`
      Optional hook to parse and execute commands. If this hook is used,
      it bypasses the normal command parsing done by the driver (including
      the MODIFY_COMMAND and NOTIFY_FAIL hooks).


    :hook:`H_MODIFY_COMMAND`
      Optional hook to modify commands (both entered or given by a
      call to command()) before the parser sees them (this includes
      special commands like 'status').


    :hook:`H_MODIFY_COMMAND_FNAME`
      Mandatory hook specifying the name of the 'modify_command'
      lfun to call for newly entered commands as result of a
      set_modify_command().


    :hook:`H_NOTIFY_FAIL`
      Mandatory hook to issue the default message if an entered
      command couldn't be parsed and no notify_fail() command is
      in effect.


    :hook:`H_SEND_NOTIFY_FAIL`
      Optional hook to send the notify fail message, regardless
      of how it was determined, to the player. If the hook is not
      set, the message is delivered using tell_object() internally.


    :hook:`H_NO_IPC_SLOT`
      Optional hook specifying the message given to logins
      rejected due to space limitations (MAX_PLAYER).


    :hook:`H_INCLUDE_DIRS`
      Semi-mandatory hook specifying the directories where <>-type
      include files are searched (this includes ""-includes not
      found as specified).


    :hook:`H_AUTO_INCLUDE`
      Optional hook specifying a string to be included before
      the source of every compiled LPC object.


    :hook:`H_TELNET_NEG`
      Optional hook to specifiy how to perform a single telnet
      negotiation. If not set, most telnet options are rejected (read:
      only a very minimal negotiation takes place).


    :hook:`H_NOECHO`
      Optional hook to specifiy how to perform the telnet actions
      to switch the echo mode (used for e.g. password input_to()s).
      If not set, a default handling is performed.

      IMPORTANT: If this hook is used, the control of all telnet
      negotiation is transferred to the mudlib (you must combine it
      with :hook:`H_TELNET_NEG` to conform to the telnet protocol).


    :hook:`H_ERQ_STOP`
      Optional hook to notify the mudlib about the termination of
      the erq demon.


    :hook:`H_MSG_DISCARDED`
      Optional hook to specify a message or take other measures
      when a message had to be discarded.

  :history 3.2.1 introduced: the hooks concept
  :history 3.2.1@1 changed: added :hook:`H_MOVE_OBJECT0` and :hook:`H_MOVE_OBJECT1`
  :history 3.2.1@34 changed: added :hook:`H_CLEAN_UP`
  :history 3.2.1@51 changed: added :hook:`H_MODIFY_COMMAND`
  :history 3.2.1@109 changed: added :hook:`H_MODIFY_COMMAND_FNAME`
  :history 3.2.1@55 changed: added :hook:`H_NOTIFY_FAILE` and :hook:`H_NO_IPC_SLOT`
  :history 3.2.1@57 changed: added :hook:`H_INCLUDE_DIRS`
  :history 3.2.1@60 changed: added :hook:`H_TELNET_NEG`
  :history 3.2.1@85 changed: added :hook:`H_NOECHO` and :hook:`H_ERQ_STOP`
  :history 3.2.7 changed: added :hook:`H_COMMAND`
  :history 3.2.9 changed: added :hook:`H_SEND_NOTIFY_FAIL` and :hook:`H_AUTO_INCLUDE`
  :history 3.3.113 changed: added :hook:`H_DEFAULT_METHOD`
  :history 3.3.163 changed: added :hook:`H_DEFAULT_PROMPT` and :hook:`H_PRINT_PROMPT`

  .. seealso:: :concept:`native`, :efun:`set_driver_hook`, :hook:`move_object`

  .. , all in (H) could be converted to an index reference?

