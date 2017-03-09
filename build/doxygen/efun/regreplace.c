public class efun {
   /**
    * This function looks through txt looking for the regular expression pattern. If it finds it, it replaces it by the replacepattern.
    * 
    * The replacepattern can be a constant string, or a closure taking the matched substring and the position at which it was found as arguments and returning the replacement pattern string.
    * 
    * The flag is a bitmask of the usual regexp options. Additionally the efun recognizes `RE_GLOBAL`: if set, the search and replace is repeated as often as the pattern matches.
    * 
    * The function returns the modified string (or the original if it wasn't modified).
    * 
    * The function behaves like the s/pattern/replacepattern/flags in editors as ed/vi or sed. The power of this function lies in replacing variable strings (as opposed to regexplode, where you can explode by regular expression, but not implode...)
    * 
    * Author
    * @subpage driver_mailto:Marcus@TAPPMud "Marcus@TAPPMud" contributed the original idea for the efun and the man page.
    * 
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * string regreplace(string txt, string pattern, closure|string replacepattern, int flags)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string msgin;
    * 
    * // Checks msgin for the string 'tells you: ' and all following
    * // characters and encloses those characters by <underline>
    * // and </underline>. global.
    * //
    * msgin = regreplace(msgin, "tells you: (.*)",
    *          "tells you: <underline>\\1</underline>", 1);
    * 
    * // replaces all <underline> html tags by the vt100 escape
    * // sequence for underline.
    * //
    * txt = regreplace(txt, "<underline>", "<ESC>[5m", 1);
    * 
    * // Put the word HOUSE into lower case.
    * txt = regreplace(txt, "HOUSE",
    *         function string (string s) {return lower_case(s);},
    *         1);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.1@125)
    * changed (3.2.9) -- accepts a closure as replacepattern
    * }
    * 
    * @see efun::regexp(), efun::regexplode(), efun::regmatch(), efun::regexp_package(), efun::sscanf(), efun::trim()
   **/
   string regreplace(string txt, string pattern, closure|string replacepattern, int flags);
}
