public class efun {
   /**
    * @synopsis{
    * int rename(string from, string to)
    * }
    * 
   **/
   int rename(string from, string to);
}
The efun rename() will move from to the new name to. If from
is a file, then to may be either a file or a directory. If
from is a directory, then to has to be a directory. If to
exists and is a directory, then from will be placed in that
directory and keep its original name.

You must have write permission for from to rename the file.

It is only possible to change name of a directory within a
directory on machines running System V, i.e. it is not
possible to move to another directory. It is not possible to
move a directory across filesystems on any system.

On successfull completion rename() will return 0. If any error
occurs, a non-zero value is returned.

EXAMPLES
      rename("/players/wizard/obj.c", "/players/wizard/newobj.c");

   See Also: 
      efun::copy_file(), efun::mkdir(), efun::rmdir(), efun::rm()
