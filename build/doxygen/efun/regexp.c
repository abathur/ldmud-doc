public class efun {
   /**
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * string * regexp(string *list, string pattern)
    * string * regexp(string *list, string pattern, int opt)
    * }
    * 
   **/
   string * regexp(string *list, string pattern, int opt);
}
Match the pattern <pattern> (interpreted according to <opt> if
given) against all strings in list, and return a new array with all
strings that matched.

If there is an error in the regular expression, a runtime
error will be raised.

EXAMPLES
string strs;
string pattern;

if (regexp_package() == RE_PCRE)
   pattern = "\<help\>.*\<me\>";

else
   pattern = "\bhelp\b.*\bme\b";

if (strs = regexp(({"please, help me Sir John."}), pattern)) {
   if (sizeof(strs)
      write("It matches.n");

}

The regular expression will test the given string (which is
packed into an array) if there is something like "help ... me"
inside of it.

LDMud 3.3 added the optional <opt> argument.
Since 3.5.0 a error is raised if RE_PCRE is specified in <opt>, but
the driver lacks PCRE support.

      See Also: 
         efun::regexplode(), efun::regmatch(), efun::regreplace(), efun::regexp_package(), efun::sscanf(),

   @ref driver_concepts_regexp "regexp"
