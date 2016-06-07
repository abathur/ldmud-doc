public class efun {
   /**
    * @synopsis{
    * int copy_file(string from, string to)
    * }
    * 
   **/
   int copy_file(string from, string to);
}
The efun copy_file() will copy the file <from> to the new name <to>.
If <to> exists and is a directory, then <from> will be placed in that
directory and keep its original name.

You must have read permission for <from> and write permission for
the target file to copy the file.

On successfull completion copy_file() will return 0. If any error
occurs, a non-zero value is returned.

EXAMPLES
copy_file("/players/wizard/obj.c", "/players/wizard/newobj.c");

LDMud 3.2.9 restricted the error behaviour to returning non-0.

   See Also: 
      efun::mkdir(), efun::rmdir(), efun::rm(), efun::rename()