.. efun:: int write_file(string file, string str)
  int write_file(string file, string str, int flags)

  Append the string :arg:`str` to the file :arg:`file`. Returns 1 for success and 0 if any failure occured.

  If :arg:`flags` is 1, the file is removed first; thus making the 'append' effectively an 'overwrite'. Default for :arg:`flags` is 0.

  .. todo:: are there defines for these values?

  :history 3.3.523 changed: added the :arg:`flags` parameter.

  .. seealso:: :efun:`file_size`, :efun:`write_bytes`, :efun:`write_file`, :efun:`read_file`, :efun:`read_bytes`, :efun:`rm`, :efun:`get_dir`
