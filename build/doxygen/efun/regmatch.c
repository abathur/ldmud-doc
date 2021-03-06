public class efun {
   /**
    * Match the string \p text against \p pattern (interpreted according to \p opt if given). If \p start is given, it is the start position for the match and must be in the range `[0..strlen(text)]`.
    * 
    * If there is no match, the result is 0. If there is a match, the exact result is determined by the flag `RE_MATCH_SUBS`:
    * 
    * If the flag `RE_MATCH_SUBS` is not set, the result is the matched expression.
    * 
    * If the flag `RE_MATCH_SUBS` is set, the result is an array of the matched string(s) of the first match. Entry [0] is the full string matching the \p pattern, following entries are the string segments matching parenthesized subexpressions in \p pattern. If a particular subexpression didn't have a match, the corresponding array entry will be 0.
    * 
    * The last entry in the array will be the new start index in case you want to repeat the match on the remaining parts of the string. This new index is usually equal the length of the match, but at least one higher than the original start index.
    * 
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * string regmatch(string text, string pattern)
    * string regmatch(string text, string pattern, int opt)
    * string regmatch(string text, string pattern, int opt, int start)
    * string * regmatch(string text, string pattern, int opt)
    * string * regmatch(string text, string pattern, int opt, int start)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * regmatch("abcdefcdf", "cd")    // "cd"
    * regmatch("abcdefcdf", "cd(e)") // "cde"
    * 
    * regmatch("abcdefcdf", "cd", RE_MATCH_SUBS)    // ({ "cd" })
    * regmatch("abcdefcdf", "cd(e)", RE_MATCH_SUBS) // ({ "cde", "e" })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.198)
    * changed (3.3.214) -- returns 0 for non-matches, and takes and returns a start position.
    * changed (3.5.0) -- an error is raised if RE_PCRE is specified in opt, but the driver lacks PCRE support.
    * }
    * 
    * @see efun::regexplode(), efun::regreplace(), efun::regexp(), efun::regexp_package()
   **/
   string * regmatch(string text, string pattern, int opt, int start);
}
