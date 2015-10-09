.. efun:: int find_call_out(string func)
  int find_call_out(closure func)

  Find the first call-out due to be executed for function <func>
  in the current object resp. for the closure <func>, and return the
  time left. If no call-out is found return -1.

  :history 3.2.1@45 chaned: can now find a call_out to a closure

  .. seealso:: :efun:`call_out`, :efun:`remove_call_out`, :efun:`call_out_info`
