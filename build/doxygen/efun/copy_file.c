public class efun {
   /**
    * Copies the file \p from to the new name \p to. If \p to exists and is a directory, then \p from will be placed in that directory and keep its original name.
    * 
    * You must have read permission for \p from and write permission for the target file to copy the file.
    * 
    * On successful completion efun::copy_file() will return 0. If any error occurs, a non-zero value is returned.
    * 
    * @synopsis{
    * int copy_file(string from, string to)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * copy_file("/players/wizard/obj.c", "/players/wizard/newobj.c");
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.9) -- restricts the error behaviour to returning non-0.
    * }
    * 
    * @see efun::mkdir(), efun::rmdir(), efun::rm(), efun::rename()
   **/
   int copy_file(string from, string to);
}
