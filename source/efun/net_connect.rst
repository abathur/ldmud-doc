.. efun:: int net_connect(string host, int port)
  :include: <comm.h>

  Open a non-blocking TCP network connection to :arg:`host` and :arg:`port`. On success, the connection is bound to the current object and the lfun :applied:`logon` is called in the object.

  Returns one of the following values:

    :macro:`NC_SUCCESS`        Success
    :macro:`NC_EUNKNOWNHOST`   the host address could not be resolved
    :macro:`NC_ENOSOCKET`      error during socket creation
    :macro:`NC_ENOBIND`        socket could not be bound
    :macro:`NC_ENOCONNECT`     socket could not be connected
  (Details of the last three errors can be found in the driver's error log.)
    :macro:`NC_ECONNREFUSED`   remote host not listening/refusing
    :macro:`NC_EMCONN`         too many pending connections (transient, try again later)
    :macro:`NC_ENORESSOURCES`  insufficient system ressources (transient, try again later)

  .. todo:: reformat above

  If the driver is configured to support IPv6, :arg:`host` is first interpreted as IPv6 hostname. If that fails, :arg:`host` is then interpretd as IPv4 hostname.

  If the connection can't be established immediately, the efun returns 'success' and the driver will check in the background for the progress of the connection. When it is established, :applied:`logon` will be called in the object. If the connection fails, ``logon(-1)`` will be called in the object.

  The efun raises a privilege violation ("net_connect", host, port).

  .. limit:: A non-blocking :efun:`connect` doesn't imply a non-blocking forward name resolution. If you provide a hostname instead of an IP address to connect to, the driver will block until the name is resolved. This may be an issue, depending on how fast your nameserver replies. Non-blocking forward DNS resolution can currently only be achieved using :macro:`ERQ_LOOKUP`.

  .. lore:: - First version 1992 by Snake and LynX for Nemesis.
    - Improved 1993 by Junky.

  :history 3.2.10 introduced:

  .. seealso:: :applied:`logon`
