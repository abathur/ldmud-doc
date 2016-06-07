public class efun {
   /**
    * @synopsis{
    * string expand_define(string name)
    * string expand_define(string name, string arg, ...)
    * }
    * 
   **/
   string expand_define(string name, string arg, ...);
}
Expands the macro <name> with the argument(s) <arg>... (default is
one empty string "").
Result is the expanded macro, or 0 if there is no macro with
that name.

This efun is applicable only while an object is compiled,
therefore its usage is restricted to a few functions like the
H_INCLUDE_DIRS driver hook, or the masters runtime_error()
function.

EXAMPLES
While compiling 'foo.c':

   expand_define("__FILE__") --> "foo.c"

Introduced in @subpage driver_mailto:3.2.1@93 "3.2.1@93".

   See Also: 
      `hooks`, master::runtime_error()
