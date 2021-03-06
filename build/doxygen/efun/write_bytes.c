public class efun {
   /**
    * Write string str to file file by overwriting the old bytes at position start. If start is a negative value then it will be counted from the end of the file. The file will not be appended, instead the function will be aborted. Returns 1 for success 0 for failure during execution.
    * 
    * @synopsis{
    * int write_bytes(string file, int start, string str)
    * }
    * 
    * @history{
    * changed (3.2@232) -- can now append to the file.
    * }
    * 
    * @see efun::save_object(), efun::write_file()
   **/
   int write_bytes(string file, int start, string str);
}
