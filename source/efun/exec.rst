.. efun:: int exec(object new, object old)

  Switches the connection from the interactive object old to the object new. If the new object is also interactive, it's connection will be transferred to the old object, thus exchaning the two connections between the object. If the new object is not interactive, the old will not be interactive anymore after the exec call succeeded.

  The result is 1 on success, and 0 on failure.

  :efun:`exec` is used to load different "user objects" or to reconnect link dead users.

  To provide security mechanisms, the interpreter calls ``master->valid_exec(current_program, new, old)``, which must return anything other than 0 to allow this :efun:`exec` invocation.

  After the :efun:`exec`, if arg 2 was ``this_player()``, ``this_player()`` becomes arg 1, else vice versa. Ditto for ``this_interactive()``.

  Take care when writing a simul-efun around :efun:`exec`: the 'current_program' passed to the :master:`valid_exec` function will be that of the simul-efun object. To get around this, use :efun:`bind_lambda` to bind ``#'exec`` to the real object and :efun:`funcall` the resulting closure.

  .. usage::

    To create a new player object, switch the connection to it, and destruct the previous object::

      ob = clone_object("std/player");
      exec(ob, this_object());
      destruct(this_object());

  :history 3.2.9 changed: adds the switchover of this_interactive().

  .. seealso:: :master:`connect`, :master:`disconnect`, :applied:`logon`, :efun:`interactive`
