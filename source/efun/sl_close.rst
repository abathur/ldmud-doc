.. efun:: void sl_close()
  :optional:

  Closes the SQLite database associated with the current object.

  The function is available only if the driver is compiled with SQLite support. In that case, :macro:`__SQLITE__` is defined.

  :history 3.3.713 introduced:

  .. seealso:: :efun:`sl_open`, :efun:`sl_exec`, :efun:`sl_insert_id`
