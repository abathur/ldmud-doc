.. efun:: void set_max_commands(int num)
  void set_max_commands(int num, object obj)

  Set the max number of commands the interactive :arg:`obj` is allowed to execute per second to :arg:`num`. A negative value means 'unlimited' and is the setting for newly created connections.

  If :arg:`obj` is not given, the current interactive is queried.

  The function raises a privilege_violation ("set_max_commands", obj, num). If the privilege is denied, the call is ignored.

  A 'command' in this context means every received data packet which causes a LPC call - actions and calls to :efun:`input_to` alike.

  .. usage::

    To establish a mud-wide default for the maximum command rate, write :master:`connect` like this::

      object connect() {
        object obj;

        ...
        set_max_commands(100);
        return obj;
      }

    Upon return from the the function, the connection with its modified max_commands will be re-bound from the master object to the returned object.

  :history 3.2.10 introduced:

  .. seealso:: :efun:`get_max_commands`, :master:`privilege_violation`
