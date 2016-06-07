public class efun {
   /**
    * @synopsis{
    * int write_file(string file, string str)
    * int write_file(string file, string str, int flags)
    * }
    * 
   **/
   int write_file(string file, string str, int flags);
}
DESCRIPTION
Append the string <str> to the file <file>. Returns 1 for success
and 0 if any failure occured.

If <flags> is 1, the file is removed first; thus making the
'append' effectively an 'overwrite'. Default for <flags> is 0.

LDMud 3.3.523 added the <flags> parameter.

      See Also: 
         efun::file_size(), efun::write_bytes(), efun::write_file(), efun::read_file(),

   efun::read_bytes(), efun::rm(), efun::get_dir()
