public class efun {
   /**
    * Return which regexp package is used by default:
    * 
    * @ref driver_topics_regexp "RE_TRADITIONAL": traditional regexps
    * @ref driver_topics_regexp "RE_PCRE":        PCRE
    * 
    * As the package can be selected at runtime through the @ref driver_hook_regexp_package "H_REGEXP_PACKAGE" driver hook, there is no good way to determine the package at LPC compile time. Match the pattern <pattern> (interpreted according to <opt> if given) against all strings in list, and return a new array with all strings that matched.
    * 
    * If there is an error in the regular expression, a runtime error will be raised.
    * 
    * @headerfile <regexp.h>
    * 
    * @synopsis{
    * int regexp_package()
    * }
    * 
    * @usage{
    * This example uses a regular expression to test the given string (which is packed into an array) if there is something like "help ... me" inside of it:
    * 
    * ~~~{.c}
    * string strs;
    * string pattern;
    * 
    * if (regexp_package() == RE_PCRE)
    *     pattern = "\\<help\\>.*\\<me\\>";
    * else
    *     pattern = "\\bhelp\\b.*\\bme\\b";
    * 
    * if (strs = regexp(({"please, help me Sir John."}), pattern)) {
    *     if (sizeof(strs)
    *         write("It matches.\n");
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.3.634)
    * }
    * 
    * @see efun::regexp(), efun::regexplode(), efun::regmatch(), efun::regreplace(), efun::sscanf(), @ref driver_hook_regexp_package "regexp_package"
   **/
   int regexp_package();
}
