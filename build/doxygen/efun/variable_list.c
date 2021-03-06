public class efun {
   /**
    * Return an array with information about \p ob variables. For every variable, 1 to 3 values (depending on \p flags) are stored in the result array conveying in this order:
    * 
    * - the name of the variable
    * - the variable flags (see below)
    * - the return type (listed in <lpctypes.h>)
    * - the value of the variable
    * 
    * \p ob may be given as true object or as a filename. In the latter case, the efun does not try to load the object before proceeding.
    * 
    * If \p ob is not the current object and the value of the variable is requested, a privilege_violation ("variable_list", <ob>) occurs.
    * 
    * \p flags determines both which information is returned for every variable, and which variables should be considered at all. Its value is created by bin-or'ing together the following flags from <functionlist.h>:
    * 
    * Control of returned information:
    * 
    *    `RETURN_FUNCTION_NAME`    include the variable name
    *    `RETURN_FUNCTION_FLAGS`   include the variable flags
    *    `RETURN_FUNCTION_TYPE`    include the return type
    *    `RETURN_VARIABLE_VALUE`   include the variable value
    *    
    * Control of listed variables:
    * 
    *    `NAME_INHERITED`      don't list if defined by inheritance
    *    `TYPE_MOD_STATIC` ==
    *    `TYPE_MOD_NOSAVE`     don't list if nosave ('static') variable
    *    `TYPE_MOD_PRIVATE`    don't list if private
    *    `TYPE_MOD_PROTECTED`  don't list if protected
    *    `NAME_HIDDEN`         don't list if not visible through inheritance
    *    
    * The 'flags' information consists of the bin-or of the list control flags given above, plus the following:
    * 
    * `TYPE_MOD_VIRTUAL`    variable is inherited virtually
    * `TYPE_MOD_NO_MASK`    variable is nomask
    * `TYPE_MOD_PUBLIC`     variable is public
    * 
    * All these flags are defined in <functionlist.h>; the return types are defined in <lpctypes.h>.
    * 
    * @headerfile <lpctypes.h>
    * 
    * @headerfile <functionlist.h>
    * 
    * @synopsis{
    * mixed * variable_list(object ob, int flags)
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see efun::inherit_list(), efun::functionlist(), efun::variable_exists()
   **/
   mixed * variable_list(object ob, int flags);
}
