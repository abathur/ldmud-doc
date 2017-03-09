public class master {
   /**
    * Used by efun::parse_command(). Return an array of common plural 'thing' ids in the installation's native language.
    * 
    * @synopsis{
    * string *parse_command_plural_id_list(void)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * string *parse_command_pural_id_list() {
    *     return: ({ "ones", "things", "them" });
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::parse_command()
   **/
   string *parse_command_plural_id_list(void);
}
