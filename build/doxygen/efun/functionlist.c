public class efun {
   /**
    * Returns an array with information about <ob>s lfunctions. For every
    * function, 1 to 4 values (depending on <flags>) are stored in
    * the result array conveying in this order:
    * 
    * - the name of the function
    * - the function flags (see below)
    * - the return type (listed in <lpctypes.h>)
    * - the number of accepted argumens
    * 
    * <ob> may be given as true object or as a filename. In the latter
    * case, the efun does not try to load the object before proceeding.
    * 
    * <flags> determines both which information is returned for every
    * function, and which functions should be considered at all.
    * Its value is created by bin-or'ing together following flags from
    * <functionlist.h>:
    * 
    * Control of returned information:
    *    RETURN_FUNCTION_NAME    include the function name
    *    RETURN_FUNCTION_FLAGS   include the function flags
    *    RETURN_FUNCTION_TYPE    include the return type
    *    RETURN_FUNCTION_NUMARG  include the number of arguments.
    *    
    *    The name RETURN_FUNCTION_ARGTYPE is defined but not implemented.
    *    
    * Control of listed functions:
    *    NAME_INHERITED      don't list if defined by inheritance
    *    TYPE_MOD_STATIC     don't list if static function
    *    TYPE_MOD_PRIVATE    don't list if private
    *    TYPE_MOD_PROTECTED  don't list if protected
    *    NAME_HIDDEN         don't list if not visible through inheritance
    *    
    * The 'flags' information consists of the bin-or of the list control
    * flags given above, plus the following:
    * 
    * TYPE_MOD_VARARGS    function takes varargs
    * NAME_UNDEFINED      function not defined yet, but referenced.
    * NAME_CROSS_DEFINED  function is defined to be in a different program
    * TYPE_MOD_NO_MASK    function is nomask
    * TYPE_MOD_PUBLIC     function is public
    * 
    * @headerfile <lpctypes.h>
    * 
    * @headerfile <functionlist.h>
    * 
    * @synopsis{
    * mixed * functionlist(object ob, int flags)
    * }
    * 
    * @see efun::inherit_list(), efun::function_exists(), efun::variable_list(), efun::call_resolved()
   **/
   mixed * functionlist(object ob, int flags);
}
