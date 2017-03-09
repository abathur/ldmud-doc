public class efun {
   /**
    * Reads a given amount of bytes from file. If \p start is not given or 0, the file is read from the beginning, else from byte \p start on. If \p start is negative, it is counted from the end of the file. \p number is the number of bytes to read. 0 or negative values are possible, but not useful. If \p start would be outside the actual size of the file, 0 is returned instead of a string.
    * 
    * The maximum bytes being read per call is `LIMIT_BYTE` (see efun::query_limits()).
    * 
    * @synopsis{
    * string read_bytes(string file, int start, int number)
    * }
    * 
    * @see efun::read_file(), efun::write_bytes(), efun::write_file()
   **/
   string read_bytes(string file, int start, int number);
}
