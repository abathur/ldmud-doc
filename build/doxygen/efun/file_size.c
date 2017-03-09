public class efun {
   /**
    * Return: 
    * - `FSIZE_NOFILE` (-1) : indicates that the file either does not exist, or that it is not readable for the calling object/user.
    * - `FSIZE_DIR` (-2) : indicates that it is a directory.
    * 
    * Returns the size of the file in bytes.
    * 
    * @headerfile <files.h>
    * 
    * @synopsis{
    * int file_size(string file)
    * }
    * 
    * @see efun::write_file(), efun::write_bytes(), efun::read_file(), efun::read_bytes(), efun::get_dir()
   **/
   int file_size(string file);
}
