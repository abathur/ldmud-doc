.. concept:: predefined
  :synopsis: Preprocessor macros predefined by the parser.
  :topic: driver

  Several preprocessor macros are pre-\ ``#defined`` by the parser to provide
  information about parser version, compile time options and parser invocation
  options:

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

    the directory path of the compiled file (in compat mode without
    leading '/').

  .. macro:: __PATH__(n)

    the directory path of the compiled file
    without the <n> trailing elements (in
    compat mode without leading '/').

  .. macro:: __VERSION__

    the version string of the driver.

  .. macro:: __VERSION_MAJOR__

    the major version number of the driver.

  .. macro:: __VERSION_MINOR__

    the minor version number of the driver.

  .. macro:: __VERSION_MICRO__

    the micro version number of the driver.

  .. macro:: __VERSION_PATCH__

    the patchlevel of the driver; a 0 here
    means 'no patchlevel'.

  .. macro:: __VERSION_COMMITID__

    the commit ID of the source of the driver
    (attention it might be <unknown>, if the
    driver was not compiled from a git
    repository)

  .. macro:: __VERSION_LOCAL__

    the (optional) LOCAL_LEVEL, the user has
    defined.


  .. macro:: __DOMAIN_NAME__

    the domain the host is part of.

  .. macro:: __HOST_IP_NUMBER__

    the hosts IP number (as a string).

  .. macro:: __HOST_NAME__

    the full hostname.

  .. macro:: __MAX_RECURSION__

    the max count of nested function calls
    (this is config.h:MAX_USER_TRACE).

  .. macro:: __MAX_EVAL_COST__

    the max evaluation cost.

  .. macro:: __RESET_TIME__

    default interval time between object
    resets.

  .. macro:: __CLEANUP_TIME__

    default interval time between object
    cleanups.

  .. macro:: __ALARM_TIME__

    the configured timing granularity.

  .. macro:: __HEART_BEAT_INTERVAL__

    the configured heartbeat time.

  .. macro:: __SYNCHRONOUS_HEART_BEAT__

    defined if synchronous heartbeats are
    enabled.

  .. macro:: __MAX_COMMAND_LENGTH__

    the maximum length a command can have.

  .. macro:: __EFUN_DEFINED__(name)

    if the efun 'name' exists, this
    macro evaluates to " 1 ", else to " 0 ".

  .. macro:: __DRIVER_LOG__

    the name of the default debug.log file
    (within the mudlib); undefined if a
    different name has been specified on the
    commandline.

  .. macro:: __WIZLIST__

    the name of the (mudlib) file from where
    the driver read the initial WIZLIST
    information. It is undefined if the driver
    was configured to not read the
    information.


  .. macro:: __MAX_MALLOC__

    the internal upper limit for total memory
    usage.

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

    the time() the driver was started.

  If the ERQ is supported, the following macros are defined:


  .. macro:: __ERQ_MAX_SEND__

    the max size of the send buffer.

  .. macro:: __ERQ_MAX_REPLY__

    the max size of the reply buffer.

  The following macros are defined if their associated package
  has been compiled into the driver:

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
    http://www.randomly.org/projects/MCCP

  .. macro:: __ALISTS__

    support for alists.

  .. macro:: __PCRE__

    support for PCRE (always defined).

  .. macro:: __TLS__

    support for TLS (internal).

  .. macro:: __GNUTLS__

    if __TLS__: TLS support provided by GnuTLS.

  .. macro:: __OPENSSL__

    if __TLS__: TLS support provided by OpenSSL.

  .. macro:: __GCRYPT__

    cryptographic routines provided by libgcrypt.

  .. macro:: __DEPRECATED__

    support for obsolete and deprecated efuns.

  :history 3.2.1 introduced: added __DOMAIN_NAME__, __HOST_IP_NUMBER__,
    __HOST_NAME__, __MAX_RECURSION__, __EFUN_DEFINED__().

  :history 3.2.1 changed: changed __DOMAIN_NAME__, __HOST_IP_NUMBER__,
    __HOST_NAME__, __MAX_RECURSION__, __EFUN_DEFINED__().

  :history 3.2.5 changed: added __COMPAT_MODE__, __NATIVE_MODE__, __EUIDS__,
    __ERQ_MAX_SEND__ and __ERQ_MAX_REPLY__.
  :history 3.2.6 changed: added __MAX_EVAL_COST__.
  :history 3.2.7 changed: added __STRICT_EUIDS__ and made __EUIDS__ standard.
  :history 3.2.8 changed: added __IPV6__, __LPC_NOSAVE__, __DIR__, __PATH__().
  :history 3.2.9 changed: added __LDMUD__, __MYSQL__, __DEPRECATED__, __VERSION_MAJOR__,
    __VERSION_MINOR__, __VERSION_MICRO__, __VERSION_PATCH__,
    __INT_MAX__, __INT_MIN__, __FLOAT_MIN__, __FLOAT_MAX__,
    __CATCH_EVAL_COST__, __MASTER_EVAL_COST__, __RESET_TIME__,
    __CLEANUP_TIME__, __DRIVER_LOG__, and __WIZLIST__.
  :history 3.2.10 changed: added __MAX_MALLOC__, __MSDOS_FS__, __LPC_ARRAY_CALLS__
    and __FILENAME_SPACES__.
  :history 3.3 changed: made __LPC_NOSAVE__ always defined and added __ALISTS__,
    __MCCP__, __LPC_STRUCTS__, __LPC_INLINE_CLOSURES__, __PGSQL__,
    __PTHREADS__, __TLS__, __BOOT_TIME__, __ALARM_TIME__,
    __HEART_BEAT_INTERVAL__, __SYNCHRONOUS_HEART_BEAT__, and __PCRE__.
  :history 3.3.713 changed: added __IDNA__, __SQLITE__.
  :history 3.3.714 changed: added __OPENSSL__, __GNUTLS__.
  :history 3.3.718 changed: added __XML_DOM__.
  :history 3.3.719 changed: removed __PTHREADS__, AMIGA, MSDOS_FS, __BEOS__
    and added __GCRYPT__.
  :history 3.3.721 changed: added __FUNCTION__.
  :history 3.5.0 changed: changed __LPC_STRUCTS__, __LPC_INLINE_CLOSURES__,
    __LPC_ARRAY_CALLS__ to be always on.
    removed __ALISTS__

  .. seealso:: :lang:`pragma`, :lang:`preprocessor`
