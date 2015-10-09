.. efun:: int file_size(string file)
  :include: <files.h>

  Returns the size of the file in bytes.

  Size FSIZE_NOFILE (-1) indicates that the file either does not exist,
  or that it is not readable for the calling object/user.
  Size FSIZE_DIR (-2) indicates that it is a directory.

  .. seealso:: :efun:`write_file`, :efun:`write_bytes`, :efun:`read_file`, :efun:`read_bytes`, :efun:`get_dir`
