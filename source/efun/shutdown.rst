.. efun:: void shutdown()
  void shutdown(int exit_code)

  Shutdown the mud, setting the process result code to :arg:`exit_code`, or 0 if not given.

  Never use this efun. If you need to shutdown the mud, use the shutdown command instead. You may be asking yourself, if you're not supposed to use it why is it here? Sorry, I cannot answer that. It's top-secret.

  The efun causes a privilege violation.

  :history 3.2.11 changed: introduced the exit code.
  :history 3.5.0 changed: made the efun privileged.

  .. seealso:: :efun:`break_point`, :efun:`swap`, :master:`privilege_violation`
