.. efun:: mixed limited(closure fun)
  mixed limited(closure fun, int tag, int value, ...)
  mixed limited(closure fun, int *limits)
  mixed limited(closure fun, int *limits, mixed *args)
  :include: <rtlimits.h>

  Call the function :arg:`fun` with any given :arg:`args` as parameters, and execute it with the given runtime limits.

  After the function exits, the currently active limits are restored. Result of the efun is the result of the closure call.

  The runtime limits can be given in two ways: as an array (like the one returned from :efun:`query_limits`, or as a list of tagged values. If the efun is used without any limit specification, all limits are supposed to be 'unlimited'.

  The limit settings recognize three special values:

  - :macro:`LIMIT_UNLIMITED`: the limit is deactivated
  - :macro:`LIMIT_KEEP`:      the former setting is kept
  - :macro:`LIMIT_DEFAULT`:   the 'global' default setting is used.

  For :macro:`LIMIT_COST`, the special values have these meaning:

  - :macro:`LIMIT_UNLIMITED`: at maximum 1 tick is accounted
  - :macro:`LIMIT_KEEP`:      :macro:`LIMIT_COST` is set to 0
  - :macro:`LIMIT_DEFAULT`:   :macro:`LIMIT_COST` is set to -100

  The efun causes a privilege violation ("limited", current_object, fun, limits-array).

  .. usage::

    Execute function with no limits at all::

      limited(#'func)

    Executes func with an eval_cost limit of 200000, and calls func as ``<func>("foo")``::

      limited(#'func, ({ 200000 }), "foo")

    Executes func with an eval_cost limit of 200000, and calls func as ``<func>("foo")``::

      limited(lambda(0, ({#'func, "foo"})), LIMIT_EVAL, 200000)

  :history 3.2.7 introduced:
  :history 3.3.563 changed: added :macro:`LIMIT_COST`.
  :history 3.3.677 changed: added :macro:`LIMIT_MAPPING_KEYS`, :macro:`LIMIT_MAPPING_SIZE`.
  :history 3.5.0 changed: added :macro:`LIMIT_MEMORY`.

  .. seealso:: :efun:`query_limits`, :efun:`set_limits`
