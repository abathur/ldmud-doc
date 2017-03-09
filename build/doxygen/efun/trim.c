public class efun {
   /**
    * Remove all leading and trailing characters \p ch from the string \p s and return the new string.
    * 
    * \p ch may be given as a single character, or a string of characters. If \p ch is not given, it defaults to the whitespace `" \t"`.
    * 
    * \p where can be used to modify where the characters are removed:
    * 
    * `TRIM_LEFT`  (1):      remove the leading characters
    * `TRIM_RIGHT` (2):      remove the trailing characters
    * `TRIM_BOTH`  (3 or 0): remove both leading and trailing characters
    * 
    * @headerfile <strings.h>
    * 
    * @synopsis{
    * string trim(string s)
    * string trim(string s, int where)
    * string trim(string s, int where, int ch)
    * string trim(string s, int where, string ch)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * trim("   1234   ")                  --> "1234"
    * trim("   1234   ", TRIM_RIGHT)      --> "   1234"
    * trim("   1234   ", TRIM_BOTH, " 1") --> "234"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * }
    * 
    * @see efun::regreplace()
   **/
   string trim(string s, int where, string ch);
}
