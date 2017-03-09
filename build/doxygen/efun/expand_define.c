public class efun {
   /**
    * Expands the macro \p name with the argument(s) \p arg ... (default is one empty string ""). Result is the expanded macro, or 0 if there is no macro with that name.
    * 
    * This efun is applicable only while an object is compiled, therefore its usage is restricted to a few functions like @ref driver_hook_include_dirs "H_INCLUDE_DIRS", or master::runtime_error().
    * 
    * @synopsis{
    * string expand_define(string name)
    * string expand_define(string name, string arg, ...)
    * }
    * 
    * @usage{
    * While compiling 'foo.c':
    * 
    * ~~~{.c}
    * expand_define("__FILE__") --> "foo.c"
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.1@93)
    * }
    * 
    * @see @ref driver_hook_overview "hook", master::runtime_error()
   **/
   string expand_define(string name, string arg, ...);
}
