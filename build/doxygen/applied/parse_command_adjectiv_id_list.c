public class applied {
   /**
    * Return all adjectives associated with this object.
    * 
    * Used by efun::parse_command().
    * 
    * @synopsis{
    * string *parse_command_adjectiv_id_list(void)
    * }
    * 
    * @usage{
    * To return an array containing a single adjective:
    * string * parse_command_adjectiv_id_list() {
    *     return ({ "iffish" });
    * }
    * }
    * 
    * @see efun::parse_command()
   **/
   string *parse_command_adjectiv_id_list(void);
}
