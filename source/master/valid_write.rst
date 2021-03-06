.. master:: string valid_write(string path, string uid, string func, object ob)

  This function is called to check if the object :arg:`ob` with the user-id :arg:`uid` has write permissions to the file given by :arg:`path` for the operation named by :arg:`func`. It should return 0 if permission is denied, or the normalized path if permission is granted. You can also return 1 to indicate that the :arg:`path` can be used unchanged.

  The returned pathname must not contain "..", a leading / will be stripped by the interpreter. By default, the returned path must also not contain space characters; if the driver is instructed to allow them, the preprocessor :macro:`__FILENAME_SPACES__` is defined.

  .. todo:: again, re: table, deflist, etc.

  :arg:`func` denotes the efun call or other operation that caused :master:`valid_write` to be called:

  ==================  ================================================
  operation           notes
  ==================  ================================================
  copy_file           for the target file or directory name
  rename_from         :efun:`rename`, for the original name
  rename_to           :efun:`rename`, for the new name
  ed_start            whenever the builtin ed tries to write to a file
  garbage_collection
  mkdir
  memdump
  objdump
  opcdump
  remove_file         :efun:`rm`
  rmdir
  save_object
  write_bytes
  write_file
  ==================  ================================================

  For :efun:`save_object`, the :arg:`path` passed is the filename as given in the efun call. If for this efun a filename ending in ".c" is returned, the ".c" will be stripped from the filename.

  .. tip:: This function is called in compat mode as well. If you need to be compatible with the old 2.4.5-mudlib, redirect these calls to ``valid_read`` or ``valid_write`` lfuns in the user object.

  :history 3.2.8 changed: adds operation "copy_file", and replaces "do_rename" with "rename_from" and "rename_to".
  :history 3.2.9 changed: adds operation "garbage_collection".
  :history 3.3.526 changed: adds operation "memdump".

  .. seealso:: :master:`valid_read`, :master:`make_path_absolute`
