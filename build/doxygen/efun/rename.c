public class efun {
   /**
    * Moves \p from to the new name \p to. If \p from is a file, then \p to may be either a file or a directory. If \p from is a directory, then \p to has to be a directory. If \p to exists and is a directory, then \p from will be placed in that directory and keep its original name.
    * 
    * You must have write permission for \p from to rename the file.
    * 
    * It is only possible to change name of a directory within a directory on machines running System V, i.e. it is not possible to move to another directory. It is not possible to move a directory across filesystems on any system.
    * 
    * On successfull completion efun::rename() will return 0. If any error occurs, a non-zero value is returned.
    * 
    * @synopsis{
    * int rename(string from, string to)
    * }
    * 
    * @usage{
    * `rename("/players/wizard/obj.c", "/players/wizard/newobj.c");`
    * 
    * }
    * 
    * @see efun::copy_file(), efun::mkdir(), efun::rmdir(), efun::rm()
   **/
   int rename(string from, string to);
}
