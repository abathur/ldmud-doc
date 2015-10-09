.. efun:: void set_auto_include_string (string arg)
  :removed:

  The arg will be automatically included into every compiled LPC
  object. This is useful to enforce global definitions, e.g.
  ``#pragma rtt_checks'' or ``#pragma strict_types''.  The
  calling object needs to be privileged by the master object.

  Note that the auto-include-string is cleared when the master
  object is reloaded.

.. history
  :history 3.2.9 deprecated: replaced this efun with driver hook H_AUTO_INCLUDE. This old version is available if the driver is compiled
    with USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :efun:`set_driver_hook`, :master:`privilege_violation`, :lang:`pragma`, :master:`master`
