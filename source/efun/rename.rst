.. efun:: int rename(string from, string to)

  Moves :arg:`from` to the new name :arg:`to`. If :arg:`from` is a file, then :arg:`to` may be either a file or a directory. If :arg:`from` is a directory, then :arg:`to` has to be a directory. If :arg:`to` exists and is a directory, then :arg:`from` will be placed in that directory and keep its original name.

  You must have write permission for :arg:`from` to rename the file.

  It is only possible to change name of a directory within a directory on machines running System V, i.e. it is not possible to move to another directory. It is not possible to move a directory across filesystems on any system.

  On successfull completion :efun:`rename` will return 0. If any error occurs, a non-zero value is returned.

  .. usage::

    ``rename("/players/wizard/obj.c", "/players/wizard/newobj.c");``

  .. seealso:: :efun:`copy_file`, :efun:`mkdir`, :efun:`rmdir`, :efun:`rm`
