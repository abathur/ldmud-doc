.. master:: int valid_trace(string what, int|string arg)

  Check if the interactive user is allowed to use tracing.

  The argument :arg:`what` denotes the action for which permission is to be checked, :arg:`arg` is the argument given to :efun:`trace`.

  .. todo:: replace table with def list?

  =============  =========================================
  :arg:`what`    notes
  =============  =========================================
  "trace"        Is the user allowed to use tracing? :arg:`arg` is the tracelevel argument given.
  "traceprefix"  Is the user allowed to set a traceprefix? :arg:`arg` is the prefix given.
  =============  =========================================

  .. seealso:: :efun:`trace`, :concept:`memory`
