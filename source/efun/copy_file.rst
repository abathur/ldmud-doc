.. efun:: int copy_file(string from, string to)

  Copies the file :arg:`from` to the new name :arg:`to`. If :arg:`to` exists and is a directory, then :arg:`from` will be placed in that directory and keep its original name.

  You must have read permission for :arg:`from` and write permission for the target file to copy the file.

  On successful completion :efun:`copy_file` will return 0. If any error occurs, a non-zero value is returned.

  .. usage::

    ::

      copy_file("/players/wizard/obj.c", "/players/wizard/newobj.c");

  :history 3.2.9 changed: restricts the error behaviour to returning non-0.

  .. seealso:: :efun:`mkdir`, :efun:`rmdir`, :efun:`rm`, :efun:`rename`
