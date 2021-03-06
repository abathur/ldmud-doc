.. efun:: string read_bytes(string file, int start, int number)

  Reads a given amount of bytes from file. If :arg:`start` is not given or 0, the file is read from the beginning, else from byte :arg:`start` on. If :arg:`start` is negative, it is counted from the end of the file. :arg:`number` is the number of bytes to read. 0 or negative values are possible, but not useful. If :arg:`start` would be outside the actual size of the file, 0 is returned instead of a string.

  The maximum bytes being read per call is :macro:`LIMIT_BYTE` (see :efun:`query_limits`).

  .. seealso:: :efun:`read_file`, :efun:`write_bytes`, :efun:`write_file`
