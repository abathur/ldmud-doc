public class master {
   /**
    * Generate the pathname of an inherited object.
    * 
    * Arguments:
    * 
    * `previous_object()`
    *    The object causing the compile.
    *    
    * file
    *    The name given in the inherit directive.
    *    
    * compiled_file
    *    The object file which is just compiled. (compat: name given without leading "/")
    *    
    * Result:
    * 
    * `0`
    *    use the given filename as it is.
    *    
    * `<path>`
    *    the full absolute pathname of the file to inherit, without parentdir parts ("/../"). Leading slashes ("/") are ignored.
    *    
    * else
    *    The inherit directive is not legal.
    *    
    * @synopsis{
    * mixed inherit_file(string file, string compiled_file)
    * }
    * 
    * @history{
    * introduced (3.2.8)
    * }
    * 
    * @see @ref driver_hook_overview "hook", master::include_file()
   **/
   mixed inherit_file(string file, string compiled_file);
}
