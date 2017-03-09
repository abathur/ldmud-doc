public class applied {
   /**
    * Return the plural names of this object.
    * 
    * If this function doesn't exist, the parser tries to pluralize the names returned by applied::parse_command_id_list().
    * 
    * Used by efun::parse_command().
    * 
    * @synopsis{
    * string *parse_command_plural_id_list(void)
    * }
    * 
    * @see efun::parse_command(), applied::parse_command_id_list()
   **/
   string *parse_command_plural_id_list(void);
}
