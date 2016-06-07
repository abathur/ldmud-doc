public class master {
   /**
    * Used by parse_command(). Return an array of common
    * singular 'thing' ids in the installation's native language.
    * 
    * @synopsis{
    * string *parse_command_id_list(void)
    * }
    * 
    * @usage{
    * string *parse_command_id_list() {
    *     return ({ "one", "thing" });
    * }
    * }
    * 
    * @see efun::parse_command()
   **/
   string *parse_command_id_list(void);
}
