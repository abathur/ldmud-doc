public class efun {
   /**
    * @synopsis{
    * string make_shared_string(string str)
    * }
    * 
   **/
   string make_shared_string(string str);
}
Puts <str> in the table of shared strings of the game.

If the string is used by several variables/objects this
saves memory. Keys of alists and mappings are always shared
strings.

In LDMud 3.3, this function is no longer necessary: strings
are shared as much as possible anyway, and the driver automatically
converts untabled strings into tabled strings after some time.

Introduced in LDMud 3.2.6; following a suggestion from Tubmud.
Deprecated in LDMud 3.3.531.
