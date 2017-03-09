public class efun {
   /**
    * Returns an array with information about functions defined in \p ob. For every function, 1 to 4 values (depending on \p flags) are stored in the result array conveying in this order:
    * 
    * - the name of the function
    * - the function flags (see below)
    * - the return type (listed in `<lpctypes.h>`)
    * - the number of accepted argumens
    * 
    * \p ob may be given as true object or as a filename. In the latter case, the efun does not try to load the object before proceeding.
    * 
    * \p flags determines both which information is returned for every function, and which functions should be considered at all. Its value is created by bin-or'ing together following flags from <functionlist.h>:
    * 
    * The 'flags' information consists of the bin-or of the list control flags given above, plus the following:
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
