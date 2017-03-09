public class efun {
   /**
    * Returns the index of \p str2 in \p str, searching from position \p pos on.
    * 
    * The returned index is relative to the beginning of the string. If \p str2 is not found in \p str, -1 is returned.
    * 
    * If \p pos is negative, it designates the start position relative to the end of the string (the search will still proceed towards the end of the string).
    * 
    * @synopsis{
    * int strstr(string str, string str2)
    * int strstr(string str, string str2, int pos)
    * }
    * 
    * @see efun::strrstr(), efun::strlen(), efun::sscanf(), efun::sprintf(), efun::explode()
   **/
   int strstr(string str, string str2, int pos);
}
