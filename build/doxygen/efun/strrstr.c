public class efun {
   /**
    * Returns the index of the first occurence of \p str2 in \p str searching from position \p pos (default: `-1 == string end`) on backward. In other words: the index of the last occurance of \p str2 before the given position \p pos.
    * 
    * The returned index is relative to the beginning of the string.
    * 
    * If \p str2 is not found in \p str, -1 is returned.
    * 
    * If \p pos is negative, it designates the start position relative to the end of the string (the search will still proceed towards the beginning of the string).
    * 
    * @synopsis{
    * int strrstr(string str, string str2)
    * int strrstr(string str, string str2, int pos)
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see efun::strstr(), efun::strlen(), efun::sscanf(), efun::sprintf(), efun::explode()
   **/
   int strrstr(string str, string str2, int pos);
}
