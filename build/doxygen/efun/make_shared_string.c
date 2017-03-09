public class efun {
   /**
    * Puts \p str in the table of shared strings of the game.
    * 
    * If the string is used by several variables/objects this saves memory. Keys of alists and mappings are always shared strings.
    * 
    * In LDMud 3.3, this function is no longer necessary: strings are shared as much as possible anyway, and the driver automatically converts untabled strings into tabled strings after some time.
    * 
    * @synopsis{
    * string make_shared_string(string str)
    * }
    * 
    * @history{
    * introduced (3.2.6) -- following a suggestion from Tubmud.
    * deprecated (3.3.531) -- This function is no longer necessary because strings are shared as much as possible anyway, and the driver automatically converts untabled strings into tabled strings after some time.
    * }
    * 
   **/
   string make_shared_string(string str);
}
