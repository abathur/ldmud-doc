.. efun:: int write_bytes(string file, int start, string str)

  Write string str to file file by overwriting the old bytes at
  position start. If start is a negative value then it will be
  counted from the end of the file. The file will not be
  appended, instead the function will be aborted. Returns 1 for
  success 0 for failure during execution.

  .. note:: since version 3.2@232, write_bytes() is able to append
  to the file.

  .. seealso:: :efun:`save_object`, :efun:`write_file`
