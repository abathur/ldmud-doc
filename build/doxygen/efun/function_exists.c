public class efun {
   /**
    * Look up a function \p str in the current object, respectively in the object \p ob. Depending on the value of \p flags, one of the following informations is returned:
    * 
    * \p flags == `FEXISTS_PROGNAME` (0, default):
    * Return the name of the program the function is defined in. This can be either `object_name(ob)`, or the name of an inherited program. If !compat mode, the returned name always begins with a '/'.
    * 
    * \p flags == `FEXISTS_FILENAME` (1):
    * Return the name of the file the function is defined in (this may be an include file). If !compat mode, the returned name always begins with a '/'.
    * 
    * \p flags == `FEXISTS_LINENO` (2):
    * Return the line number within the source file.
    * 
    * \p flags == `FEXISTS_ALL` (3):
    * Return an array with all the above information, plus information about the function type/flags/number of arguments.
    * 
    * The returned array contains this information:
    *    string [`FEXISTS_PROGNAME`]: the program name
    *    string [`FEXISTS_FILENAME`]: the filename
    *    int    [`FEXISTS_LINENO`]:   the linenumber
    *    int    [`FEXISTS_NUMARG`]:   the number of arguments to the function
    *    int    [`FEXISTS_TYPE`]:     the return type of the function
    *    int    [`FEXISTS_FLAGS`]:    the function flags
    *    
    * The \p flags value can be or-ed to `NAME_HIDDEN` to return information about static and protected functions in other objects. It is not possible to return information about private functions.
    * 
    * If the function cannot be found (because it doesn't exist or it is not visible to the caller), the result is 0.
    * 
    * @headerfile <functionlist.h>
    * 
    * @synopsis{
    * mixed function_exists(string str)
    * mixed function_exists(string str, int flags)
    * mixed function_exists(string str, object ob)
    * mixed function_exists(string str, object ob, int flags)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * function_exists("create")
    * function_exists("create", that_object, NAME_HIDDEN|FEXISTS_ALL);
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.10) -- broadened the range of returned values and introduced the flags argument.
    * changed (3.2.12/3.3.713) -- added the function type/flags/number of arguments to the result of FEXISTS_ALL.
    * }
    * 
    * @see efun::call_other(), efun::call_resolved(), efun::functionlist(), efun::variable_exists()
   **/
   mixed function_exists(string str, object ob, int flags);
}
