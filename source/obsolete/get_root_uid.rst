.. master:: string get_root_uid(void)
  :removed:

  Return the string to be used as root-uid.
  Under !native, the function is expendable.

.. history
  :history 3.2.1@40 changed: get_root_uid() was renamed to get_master_uid()
    and recieved a new semantic.

  .. seealso:: :master:`get_bb_uid`, :master:`get_master_uid`, :concept:`uids`, :master:`creator_file`, :efun:`creator`
