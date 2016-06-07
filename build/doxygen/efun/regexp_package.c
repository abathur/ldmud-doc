public class efun {
   /**
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * int regexp_package()
    * }
    * 
   **/
   int regexp_package();
}
Return which regexp package is used by default:

   RE_TRADITIONAL: traditional regexps
   RE_PCRE:        PCRE

As the package can be selected at runtime through the
REGEXP_PACKAGE driver hook, there is no good way to determine
the package at LPC compile time.
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

Introduced in LDMud 3.3.634.

      See Also: 
         efun::regexp(), efun::regexplode(), efun::regmatch(), efun::regreplace(), efun::sscanf(),

   @ref driver_concepts_regexp "regexp", @ref driver_hook_regexp_package "regexp_package"