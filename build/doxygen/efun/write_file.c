public class efun {
   /**
    * Append the string \p str to the file \p file. Returns 1 for success and 0 if any failure occured.
    * 
    * If \p flags is 1, the file is removed first; thus making the 'append' effectively an 'overwrite'. Default for \p flags is 0.
    * 
    * @synopsis{
    * int write_file(string file, string str)
    * int write_file(string file, string str, int flags)
    * }
    * 
    * @history{
    * changed (3.3.523) -- added the flags parameter.
    * }
    * 
    * @see efun::file_size(), efun::write_bytes(), efun::write_file(), efun::read_file(), efun::read_bytes(), efun::rm(), efun::get_dir()
   **/
   int write_file(string file, string str, int flags);
}
