.. overview:: Driver-supported hooks
  :name: hook
  :topics: driver

  To allow a greater flexibility of the muds, the gamedrivers since 3.2.1 moved several once hardcoded 'underground' activities from the driver into the mudlib. This includes for example the differences between compat and native mode.

  The hooks are set with the privileged :efun:`set_driver_hook`. Some of the hooks are mandatory, some not. Most hooks accept unbound lambda closures as values, some also lfun closures or even strings.

  The hooks are identified by an ordinal number, for which symbolic names are defined in :file:`/sys/driverhooks.h`.

  .. include:: hook_briefs.index

  .. toctree::
    :glob:
    :maxdepth: 1

    *

  :history 3.2.1 introduced: the hooks concept
  :history 3.2.1@1 changed: added :hook:`H_MOVE_OBJECT0` and :hook:`H_MOVE_OBJECT1`
  :history 3.2.1@34 changed: added :hook:`H_CLEAN_UP`
  :history 3.2.1@51 changed: added :hook:`H_MODIFY_COMMAND`
  :history 3.2.1@109 changed: added :hook:`H_MODIFY_COMMAND_FNAME`
  :history 3.2.1@55 changed: added :hook:`H_NOTIFY_FAIL` and :hook:`H_NO_IPC_SLOT`
  :history 3.2.1@57 changed: added :hook:`H_INCLUDE_DIRS`
  :history 3.2.1@60 changed: added :hook:`H_TELNET_NEG`
  :history 3.2.1@85 changed: added :hook:`H_NOECHO` and :hook:`H_ERQ_STOP`
  :history 3.2.7 changed: added :hook:`H_COMMAND`
  :history 3.2.9 changed: added :hook:`H_SEND_NOTIFY_FAIL` and :hook:`H_AUTO_INCLUDE`
  :history 3.3.113 changed: added :hook:`H_DEFAULT_METHOD`
  :history 3.3.163 changed: added :hook:`H_DEFAULT_PROMPT` and :hook:`H_PRINT_PROMPT`

  .. seealso:: :concept:`native`, :efun:`set_driver_hook`, :hook:`move_object`, :overview:`applied`, :overview:`topics`, :overview:`efun`, :overview:`internals`, :overview:`syntax`, :overview:`master`, :overview:`obsolete`
