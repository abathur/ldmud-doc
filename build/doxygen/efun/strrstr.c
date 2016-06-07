public class efun {
   /**
    * @synopsis{
    * int strrstr(string str, string str2)
    * int strrstr(string str, string str2, int pos)
    * }
    * 
   **/
   int strrstr(string str, string str2, int pos);
}
Returns the index of the first occurence of <str2> in <str> searching
from position <pos> (default: -1 == string end) on backward.
In other words: the index of the last occurance of <str2> before
the given position <pos>.

The returned index is relative to the beginning of the string.

If <str2> is not found in <str>, -1 is returned.

If <pos> is negative, it designates the start position relative
to the end of the string (the search will still proceed towards
the beginning of the string).

Introduced in LDMud 3.2.10.

   See Also: 
      efun::strstr(), efun::strlen(), efun::sscanf(), efun::sprintf(), efun::explode()
