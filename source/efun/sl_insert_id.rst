.. efun:: int sl_insert_id()
  :optional:

  After inserting a line into a table with an AUTO_INCREMENT field,
  this efun can be used to return the (new) value of the AUTO_INCREMENT
  field.

  The function is available only if the driver is compiled with
  SQLite support. In that case, __SQLITE__ is defined.

.. history
  Added in LDMud 3.3.713.

  .. seealso:: :efun:`sl_open`, :efun:`sl_exec`, :efun:`sl_close`
