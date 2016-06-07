public class efun {
   /**
    * @synopsis{
    * string read_bytes(string file, int start, int number)
    * }
    * 
   **/
   string read_bytes(string file, int start, int number);
}
Reads a given amount of bytes from file.
If <start> is not given or 0, the file is read from the
beginning, else from the <start>th byte on. If <start> is
negative, it is counted from the end of the file.
<number> is the number of bytes to read. 0 or negative values
are possible, but not useful.
If <start> would be outside the actual size of the file, 0 is
returned instead of a string.

The maximum bytes being read per call is LIMIT_BYTE (see
query_limits()).

   See Also: 
      efun::read_file(), efun::write_bytes(), efun::write_file()
