public class efun {
   /**
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * string * regexplode(string text, string pattern)
    * string * regexplode(string text, string pattern, int opt)
    * }
    * 
   **/
   string * regexplode(string text, string pattern, int opt);
}
This function is similar to explode but accepts a regular
expression <pattern> as delimiter (interpreted according to <opt>
if given).

If flag RE_OMIT_DELIM is not set in <opt>, then every second element
in the result vector will be the text that matched the delimiter.
If the flag is set, then the result vector will contain only
the text between the delimiters.

EXAMPLES
regexplode("abcdef", "cde")                -> ({ "ab", "cde", "f" })
regexplode("abcdef", "cde", RE_OMIT_DELIM) -> ({ "ab", "f" })

Introduced in @subpage driver_mailto:3.2@61 "3.2@61".
LDMud 3.3 added the optional <opt> argument and the RE_OMIT_DELIM

   flag.

Since 3.5.0 a error is raised if RE_PCRE is specified in <opt>, but
the driver lacks PCRE support.

      See Also: 
         efun::explode(), efun::regexp(), efun::regmatch(), efun::regreplace(),

   efun::regexp_package(), @ref driver_concepts_regexp "regexp"
