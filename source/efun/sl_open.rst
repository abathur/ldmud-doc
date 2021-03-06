.. efun:: int sl_open(string filename)
  :optional:

  Opens the file :arg:`filename` for use as a SQLite database. The file will be created if it doesn't exist. Only one open file per object is allowed. On success this function returns 1, otherwise an error is usually thrown.

  The function is available only if the driver is compiled with SQLite support. In that case, :macro:`__SQLITE__` is defined.

  :history 3.3.713 introduced:

  .. seealso:: :efun:`sl_exec`, :efun:`sl_insert_id`, :efun:`sl_close`
