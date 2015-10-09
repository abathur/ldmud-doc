.. efun:: void sl_close()
  :optional:

  Closes the SQLite database associated with the current object.

  The function is available only if the driver is compiled with
  SQLite support. In that case, __SQLITE__ is defined.

.. history
  Added in LDMud 3.3.713.

  .. seealso:: :efun:`sl_open`, :efun:`sl_exec`, :efun:`sl_insert_id`
