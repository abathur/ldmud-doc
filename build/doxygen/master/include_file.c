public class master {
   /**
    * Generate the pathname of an included file.
    * 
    * Arguments:
    * 
    * `previous_object()`
    *    The object causing the compile.
    *    
    * file
    *    The name given in the #include directive.
    *    
    * compiled_file
    *    The object file which is just compiled. (compat: name given without leading "/")
    *    
    * sys_include
    *    TRUE for #include <> directives.
    *    
    * Result:
    * 
    * `0`
    *    use the normal include filename generation (""-includes are used as they are, <>-includes are handled according to @ref driver_hook_include_dirs "H_INCLUDE_DIRS").
    *    
    * `<path>`
    *    the full absolute pathname of the file to include, without parentdir parts ("/../"). Leading slashes ("/") may be omitted.
    *    
    * else
    *    The include directive is not legal.
    *    
    * If the function does not generate a valid pathname, the driver will next try to resolve the include using the @ref driver_hook_include_dirs "H_INCLUDE_DIRS" hook.
    * 
    * @synopsis{
    * mixed include_file(string file, string compiled_file, int sys_include)
    * }
    * 
    * @history{
    * introduced (3.2.8)
    * }
    * 
    * @see @ref driver_hook_overview "hook", master::inherit_file(), @ref driver_hook_include_dirs "include_dirs"
   **/
   mixed include_file(string file, string compiled_file, int sys_include);
}
