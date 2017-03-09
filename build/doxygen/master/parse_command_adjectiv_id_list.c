public class master {
   /**
    * Used by efun::parse_command(). Return an array of common adjectives in the installation's native language.
    * 
    * @synopsis{
    * string *parse_command_adjectiv_id_list(void)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string * parse_command_adjectiv_id_list() {
    *     return ({ "iffish" });
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::parse_command()
   **/
   string *parse_command_adjectiv_id_list(void);
}
