public class efun {
   /**
    * @synopsis{
    * mixed * sl_exec(string statement, ...)
    * }
    * 
   **/
   mixed * sl_exec(string statement, ...);
}
Executes the SQL statement <statement> for the current
SQLite database. The SQL statement may contain wildcards like
'?' and '?nnn', where 'nnn' is an integer. These wildcards
can be given as further parameters to sl_exec. With '?nnn'
the number of a specific parameter can be given, the first
parameter has number 1.

If the statement returns data, sl_exec returns an array
with each row (which is itself an array of columns) as
an element.

Pragma statements raise a privilege_violation ("sqlite_pragma",
ob, name, value). If the privilege is denied, an error is
thrown.

The function is available only if the driver is compiled with
SQLite support. In that case, __SQLITE__ is defined.

Added in LDMud 3.3.713.

   See Also: 
      efun::sl_open(), efun::sl_insert_id(), efun::sl_close()
