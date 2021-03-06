public class efun {
   /**
    * Return an array of strings, created when the string str is split into substrings as divided by del.
    * 
    * @par note: `implode(explode(str, del), del) == str` is always true.
    * 
    * @synopsis{
    * string * explode(string str, string del)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * function                    returns
    * -------------------------------------------------------------------
    * explode(" ab cd ef ", " ")  ({ "", "ab", "cd", "ef", "" })
    * explode("abc", "abc")       ({ "", "" })
    * explode("", "")             ({ "" })
    * explode("", <whatever>)     ({ "" })
    * explode("abc", "xyz")       ({ "abc" })
    * explode("abc", "")          ({ "a", "b", "c" })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (unknown) -- explode(" ab cd ef ", " ") formerly returned ({ "ab", "cd", "ef" }) instead of ({ "", "ab", "cd", "ef", "" }), i. e. the empty strings were ignored. The new behaviour is more consistent, because now implode(explode(str, del), del) == str is always true.
    * changed (3.5.0) -- explode("","") returns ({""}), so it is guaranteed to return a non-empty array.
    * }
    * 
    * @see efun::sscanf(), efun::implode(), efun::regexplode()
   **/
   string * explode(string str, string del);
}
