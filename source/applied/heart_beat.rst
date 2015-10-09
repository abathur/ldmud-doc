.. applied:: void heart_beat()

  This function will be called automatically every
  __HEART_BEAT_INTERVAL__ seconds. The driver will call the function
  directly in the object, even if the function is being shadowed.

  The start and stop of heart beat is controlled by the efun
  set_heart_beat(). Be careful not to have objects with heart
  beat running all the time, as it uses a lot of driver
  resources. If there is an error in the heart beat routine, the
  heart beat will be turned off for this object and the
  master function heart_beat_error() is called. If the call
  to the master function returns a non-zero value, the heart beat
  will be turned back on again.

  The function this_player() will return this object, but only if
  it is living. Otherwise, this_player() will return 0.

  Note that error messages will be given to the current user
  which will be the object itself or nobody.

  .. usage::

    .. code-block:: c

      object owner;
      void create() {
         ...
         owner=this_player();
         set_heart_beat(1);
      }
      void heart_beat() {
         tell_object(owner, "Your heart goes: BUM BUM\n");
      }

    We have to use tell_object() because write goes to the current
    user and this can only be the object itself or nobody.

  .. history

  :history 3.3.687 changed: made the interval time configurable at driver compile
    time (used to be 2 seconds fixed).

  .. seealso:: :efun:`set_heart_beat`, :efun:`call_out`, :efun:`enable_commands`, :master:`heart_beat_error`
