.. master:: string get_bb_uid(void)

  This method is called when :efun:`process_string` is used without a current object (e.g. from notify_fail method). The current object will be set to the current command giver, and will receive the euid returned from this function.

  If strict-euids, this function must exist and return a string. Otherwise the function is optional and/or may return 0.

  :history 3.2.1 changed: :master:`get_bb_uid` is needed just for :efun:`process_string` if no ``this_object()`` is present.

  .. seealso:: :concept:`uids`, :efun:`creator`, :master:`get_master_uid`
