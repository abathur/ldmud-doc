.. efun:: int sl_open(string filename)
  :optional:

Opens the file <filename> for use as a SQLite database.
The file will be created if it doesn't exist. Only one
open file per object is allowed. On success this function
returns 1, otherwise an error is usually thrown.

The function is available only if the driver is compiled with
SQLite support. In that case, __SQLITE__ is defined.

.. history
Added in LDMud 3.3.713.

  .. seealso:: :efun:`sl_exec`, :efun:`sl_insert_id`, :efun:`sl_close`
