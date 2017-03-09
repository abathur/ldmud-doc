public class efun {
   /**
    * This function is similar to explode but accepts a regular expression \p pattern as delimiter (interpreted according to \p opt if given).
    * 
    * If flag `RE_OMIT_DELIM` is not set in \p opt, then every second element in the result vector will be the text that matched the delimiter. If the flag is set, then the result vector will contain only the text between the delimiters.
    * 
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * string * regexplode(string text, string pattern)
    * string * regexplode(string text, string pattern, int opt)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * regexplode("abcdef", "cde")                // ({ "ab", "cde", "f" })
    * regexplode("abcdef", "cde", RE_OMIT_DELIM) // ({ "ab", "f" })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2@61)
    * changed (3.3) -- added the optional opt argument and the RE_OMIT_DELIM flag.
    * changed (3.5.0) -- an error is raised if RE_PCRE is specified in opt, but the driver lacks PCRE support.
    * }
    * 
    * @see efun::explode(), efun::regexp(), efun::regmatch(), efun::regreplace(), efun::regexp_package()
   **/
   string * regexplode(string text, string pattern, int opt);
}
