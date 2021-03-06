.. master:: int handle_external_signal(int signal)
  :include: <signals.h>

  If the driver receives a signal from the OS it forwards it to the mudlib master by calling this function. The signal received by the driver is given in :arg:`signal` and may be one of the following: :macro:`SIGHUP`, :macro:`SIGINT`, :macro:`SIGTERM`, :macro:`SIGUSR1`, :macro:`SIGUSR2`.

  If this function returns != 0, the driver will assume the signal has been dealt with and take NO further action. The exception is :macro:`SIGTERM`, which can't be handled. The driver will perform a graceful shutdown of the game after this function returns.

  If the master does not handle the signal (returns 0 or this function doe not exit), the driver will perform the following default actions:

  .. todo:: not clear if the below should be refs or macro directives; where should macros be defined?

  :macro:`SIGHUP`
    begin a graceful shutdown
  :macro:`SIGINT`
    send itself an unhandled :macro:`SIGINT`. This usually causes an immediate and non-graceful shutdown.
  :macro:`SIGUSR1`
    the driver will reload the master object
  :macro:`SIGUSR2`
    the driver will re-open its debug log file (this will happen the next time the driver writes to it)

