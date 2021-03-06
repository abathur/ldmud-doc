.. master:: mixed heart_beat_error(object culprit, string err, string prg, string curobj, int line, int caught)

  This function is called when a runtime error occurs while executing the :applied:`heart_beat` function of the object :arg:`culprit`. :arg:`prg` is program where the actual error happened, in object :arg:`curobj` at the given :arg:`line`.

  At time of call, the heart_beat has been turned off. Return anything != 0 to restart the heart_beat in :arg:`culprit`.

  If :arg:`culprit` is a user, it should at least get the message "You have no heartbeat". A more advanced handling would destruct the offending object :arg:`curobj` and and allow the heartbeat to restart.

  .. todo:: I question the above wisdom, but I'm a little militant about the idea of not forcing back-end abstractions on front-end users. Should a front-end user ever receive a message letting them know that there's a problem with some backend abstraction?

  If the error is caught on a higher level, :arg:`caught` is non-zero; otherwise it is 0.

  .. note:: :arg:`prg` denotes the program actually executed (which might be an inherited one) whereas :arg:`curobj` is just the offending object.

  :history 3.2.12/3.3.705 changed: added the :arg:`caught` argument.

  .. seealso:: :efun:`set_heart_beat`, :applied:`heart_beat`, :master:`runtime_error`
