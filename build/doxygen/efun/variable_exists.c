public class efun {
   /**
    * @headerfile <functionlist.h>
    * 
    * @synopsis{
    * string variable_exists(string str)
    * string variable_exists(string str, int flags)
    * string variable_exists(string str, object ob)
    * string variable_exists(string str, object ob, int flags)
    * }
    * 
   **/
   string variable_exists(string str, object ob, int flags);
}
Look up a variable <str> in the current object, respectively
in the object <ob>.

The result is the name of the program the variable is defined
in. This can be either object_name(ob), or the name of an
inherited program. If !compat mode, the returned name always
begins with a '/'.

<flags> can be passed as NAME_HIDDEN to return information
about static and protected variables in other objects. It is
not possible to return information about private variables.

If the variable cannot be found (because it doesn't exist or
it is not visible to the caller), the result is 0.

Introduced in LDMud 3.2.10.

   See Also: 
      efun::function_exists(), efun::variable_list()
