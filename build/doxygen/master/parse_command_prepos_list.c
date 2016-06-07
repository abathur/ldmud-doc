public class master {
   /**
    * Used by parse_command(). Return an array of common
    * prepositions in the installation's native language.
    * 
    * @synopsis{
    * string *parse_command_prepos_list(void)
    * }
    * 
    * @usage{
    * string *parse_command_prepos_list() {
    *     return ({ "in", "on", "under", "behind", "beside" });
    * }
    * }
    * 
    * @see efun::parse_command()
   **/
   string *parse_command_prepos_list(void);
}
