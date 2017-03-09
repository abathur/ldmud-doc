.. topic:: Driver-defined preprocessor macros
  :name: predefined
  :topics: driver

  Several preprocessor macros are pre-\ ``#defined`` by the parser to provide information about parser version, compile time options and parser invocation options:

  .. macro:: LPC3

    always defined.

  .. macro:: __LDMUD__

    always defined.

  .. macro:: __EUIDS__

    always (for compatibility).

  .. macro:: COMPAT_FLAG
    __COMPAT_MODE__

    defined if the driver runs in compat mode.

  .. macro:: __STRICT_EUIDS__

    defined if strict euid usage is enforced.

  .. macro:: __FILENAME_SPACES__

    defined if filenames may contain spaces.

  .. macro:: __MASTER_OBJECT__

    the name of the master object (in compat mode without leading '/').

  .. macro:: __FILE__

    the name of the compiled file (in compat mode without leading '/').

  .. macro:: __LINE__

    the current line number.

  .. macro:: __FUNCTION__

    the current function name.

  .. macro:: __DIR__

    the directory path of the compiled file (in compat mode without leading '/').

  .. macro:: __PATH__(n)

    the directory path of the compiled file without the *n* trailing elements (in compat mode without leading '/').

  .. macro:: __VERSION__

    the version string of the driver.

  .. macro:: __VERSION_MAJOR__

    the major version number of the driver.

  .. macro:: __VERSION_MINOR__

    the minor version number of the driver.

  .. macro:: __VERSION_MICRO__

    the micro version number of the driver.

  .. macro:: __VERSION_PATCH__

    the patchlevel of the driver; a 0 here means 'no patchlevel'.

  .. macro:: __VERSION_COMMITID__

    the commit ID of the source of the driver (attention it might be ``<unknown>``, if the driver was not compiled from a git repository)

  .. macro:: __VERSION_LOCAL__

    the (optional) LOCAL_LEVEL, the user has defined.


  .. macro:: __DOMAIN_NAME__

    the domain the host is part of.

  .. macro:: __HOST_IP_NUMBER__

    the hosts IP number (as a string).

  .. macro:: __HOST_NAME__

    the full hostname.

  .. macro:: __MAX_RECURSION__

    the max count of nested function calls (this is config.h:MAX_USER_TRACE).

  .. macro:: __MAX_EVAL_COST__

    the max evaluation cost.

  .. macro:: __RESET_TIME__

    default interval time between object resets.

  .. macro:: __CLEANUP_TIME__

    default interval time between object cleanups.

  .. macro:: __ALARM_TIME__

    the configured timing granularity.

  .. macro:: __HEART_BEAT_INTERVAL__

    the configured heartbeat time.

  .. macro:: __SYNCHRONOUS_HEART_BEAT__

    defined if synchronous heartbeats are enabled.

  .. macro:: __MAX_COMMAND_LENGTH__

    the maximum length a command can have.

  .. macro:: __EFUN_DEFINED__(name)

    if the efun 'name' exists, this macro evaluates to " 1 ", else to " 0 ".

  .. macro:: __DRIVER_LOG__

    the name of the default debug.log file (within the mudlib); undefined if a different name has been specified on the commandline.

  .. macro:: __WIZLIST__

    the name of the (mudlib) file from where the driver read the initial WIZLIST information. It is undefined if the driver was configured to not read the information.


  .. macro:: __MAX_MALLOC__

    the internal upper limit for total memory usage.

  .. macro:: __INT_MAX__

    the largest integer number.

  .. macro:: __INT_MIN__

    the smallest integer number.

  .. macro:: __FLOAT_MAX__

    the largest (positive) float number.

  .. macro:: __FLOAT_MIN__

    the smallest (positive) float number.


  .. macro:: __LPC_NOSAVE__

    always defined.

  .. macro:: __LPC_STRUCTS__

    always defined.

  .. macro:: __LPC_INLINE_CLOSURES__

    always defined.

  .. macro:: __LPC_ARRAY_CALLS__

    always defined.

  .. macro:: __BOOT_TIME__

    the :efun:`time` the driver was started.

  If the ERQ is supported, the following macros are defined:


  .. macro:: __ERQ_MAX_SEND__

    the max size of the send buffer.

  .. macro:: __ERQ_MAX_REPLY__

    the max size of the reply buffer.

  The following macros are defined if their associated package has been compiled into the driver:

  .. macro:: __IDNA__

    support for IDNA.

  .. macro:: __IPV6__

    support for IP v.6.

  .. macro:: __MYSQL__

    support for mySQL.

  .. macro:: __PGSQL__

    support for PostgreSQL.

  .. macro:: __SQLITE__

    support for SQLite 3.

  .. macro:: __XML_DOM__

    support for XML parsing.

  .. macro:: __MCCP__

    support for MCCP.

    .. todo:: above had a link to http://www.randomly.org/projects/MCCP, but I've cut it since it's just a domain parking page; not sure if we want/need/can provide a fresh link.

  .. macro:: __ALISTS__

    support for alists.

  .. macro:: __PCRE__

    support for PCRE (always defined).

  .. macro:: __TLS__

    support for TLS (internal).

  .. macro:: __GNUTLS__

    if :macro:`__TLS__`: TLS support provided by GnuTLS.

  .. macro:: __OPENSSL__

    if :macro:`__TLS__`: TLS support provided by OpenSSL.

  .. macro:: __GCRYPT__

    cryptographic routines provided by libgcrypt.

  .. macro:: __DEPRECATED__

    support for obsolete and deprecated efuns.

    .. todo:: this should link to a list of efuns with status deprecated (and obsolete?!), if possible

  .. todo:: native mode is added but never noted as removed below

  :history 3.2.1 changed: changed :macro:`__DOMAIN_NAME__`, :macro:`__HOST_IP_NUMBER__`, :macro:`__HOST_NAME__`, :macro:`__MAX_RECURSION__`, :macro:`__EFUN_DEFINED__()`.
  :history 3.2.5 changed: added :macro:`__COMPAT_MODE__`, ``__NATIVE_MODE__``, :macro:`__EUIDS__`, :macro:`__ERQ_MAX_SEND__` and :macro:`__ERQ_MAX_REPLY__`.
  :history 3.2.6 changed: added :macro:`__MAX_EVAL_COST__`.
  :history 3.2.7 changed: added :macro:`__STRICT_EUIDS__` and made :macro:`__EUIDS__` standard.
  :history 3.2.8 changed: added :macro:`__IPV6__`, :macro:`__LPC_NOSAVE__`, :macro:`__DIR__`, :macro:`__PATH__()`.
  :history 3.2.9 changed: added :macro:`__LDMUD__`, :macro:`__MYSQL__`, :macro:`__DEPRECATED__`, :macro:`__VERSION_MAJOR__`, :macro:`__VERSION_MINOR__`, :macro:`__VERSION_MICRO__`, :macro:`__VERSION_PATCH__`, :macro:`__INT_MAX__`, :macro:`__INT_MIN__`, :macro:`__FLOAT_MIN__`, :macro:`__FLOAT_MAX__`, ``__CATCH_EVAL_COST__``, ``__MASTER_EVAL_COST__``, :macro:`__RESET_TIME__`, :macro:`__CLEANUP_TIME__`, :macro:`__DRIVER_LOG__`, and :macro:`__WIZLIST__`.
  :history 3.2.10 changed: added :macro:`__MAX_MALLOC__`, ``__MSDOS_FS__``, :macro:`__LPC_ARRAY_CALLS__` and :macro:`__FILENAME_SPACES__`.
  :history 3.3 changed: - :macro:`__LPC_NOSAVE__` are now always defined
    - added :macro:`__ALISTS__`, :macro:`__MCCP__`, :macro:`__LPC_STRUCTS__`, :macro:`__LPC_INLINE_CLOSURES__`, :macro:`__PGSQL__`, ``__PTHREADS__``, :macro:`__TLS__`, :macro:`__BOOT_TIME__`, :macro:`__ALARM_TIME__`, :macro:`__HEART_BEAT_INTERVAL__`, :macro:`__SYNCHRONOUS_HEART_BEAT__`, and :macro:`__PCRE__`.
  :history 3.3.713 changed: added :macro:`__IDNA__`, :macro:`__SQLITE__`.
  :history 3.3.714 changed: added :macro:`__OPENSSL__`, :macro:`__GNUTLS__`.
  :history 3.3.718 changed: added :macro:`__XML_DOM__`.
  :history 3.3.719 changed: removed __PTHREADS__, AMIGA, MSDOS_FS, __BEOS__ and added :macro:`__GCRYPT__`.
  :history 3.3.721 changed: added :macro:`__FUNCTION__`.
  :history 3.5.0 changed: - :macro:`__LPC_STRUCTS__`, :macro:`__LPC_INLINE_CLOSURES__`, :macro:`__LPC_ARRAY_CALLS__` are now always on.
    - removed ``__ALISTS__``

  .. seealso:: :syntax:`pragma`, :syntax:`preprocessor`
