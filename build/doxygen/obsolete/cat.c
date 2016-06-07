public class efun {
   /**
    * List the file found at path.
    * 
    * In most installations it is not legal to have '..' or spaces
    * in the path. This commands is normally connected to the "cat"
    * command that wizards have. It is also used by the "help"
    * command. The optional arguments start and num are start line
    * number and number of lines. If they are not given the whole
    * file is printed from the beginning.
    * 
    * The total number of lines will not exceed a system limit, which
    * normally is 50 lines.
    * 
    * cat() returns the number of lines read and printed if success,
    * 0 if no such file or no lines to read (if start or len is < 0,
    * or if the file has less than start lines).
    * 
    * This efun has been deprecated in 3.3.719. Please don't use it in new
    * code. Use either a combination of read_bytes() + tell_object() or the
    * sefun cat() from the driver package.
    * 
    * @synopsis{
    * int cat(string path, int start, int num)
    * }
    * 
    * @usage{
    * This will print out the file "/doc/efun/cat" begining at line
    * 5 and ending with line 13:
    * cat("/doc/efun/cat", 5, 9);
    * }
    * 
    * @history{
    * deprecated (3.3.719)
    * removed (3.5.0)
    * }
    * 
    * @see efun::get_dir(), efun::file_size(), efun::read_file(), efun::read_bytes(), master::valid_read()
   **/
   int cat(string path, int start, int num);
}
