public class efun {
   /**
    * @synopsis{
    * int strstr(string str, string str2)
    * int strstr(string str, string str2, int pos)
    * }
    * 
   **/
   int strstr(string str, string str2, int pos);
}
Returns the index of <str2> in <str>, searching from position <pos>
on.

The returned index is relative to the beginning of the string.
If <str2> is not found in <str>, -1 is returned.

If <pos> is negative, it designates the start position relative
to the end of the string (the search will still proceed towards
the end of the string).

   See Also: 
      efun::strrstr(), efun::strlen(), efun::sscanf(), efun::sprintf(), efun::explode()