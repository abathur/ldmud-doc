.. efun:: int remove_call_out(string fun)
  int remove_call_out(closure fun)

  Remove next pending call-out for function :arg:`fun` in the current object, resp. the next pending call-out for closure :arg:`fun`. The time left is returned.

  -1 is returned if there were no call-outs pending to this function.

  .. usage::

    To remove every pending call-out to ``MyTimer()``::

      while (remove_call_out("MyTimer") != -1) continue;

  :history 3.2.1 changed: can now remove a call_out to a closure

  .. seealso:: :efun:`call_out`, :efun:`call_out_info`, :efun:`find_call_out`
