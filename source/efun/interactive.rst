.. efun:: int interactive()
  int interactive(object ob)

  Return non-zero if :arg:`ob` is an interactive user. If :arg:`ob` is omitted, ``this_object()`` will be used. The return value is 1 if the object :arg:`ob` is interactive, else 0.

  .. seealso:: :efun:`query_once_interactive`, :efun:`query_ip_number`, :efun:`query_ip_name`, :efun:`query_idle`
