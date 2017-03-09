public class efun {
   /**
    * Returns info about the type of \p value, as controlled by the flag.
    * 
    * If the optional argument \p flag is not given, an array is returned whose first element is an integer denoting the data type, as defined in <lpctypes.h>. The second entry can contain additional information about \p value.
    * 
    * If \p flag flag is the number 0, only the first element of that array (i.e. the data type) is returned (as int). If \p flag is 1, the second element is returned.
    * 
    * If \p value is a closure, the \p flag setting 2 lets the efun return the object of the closure (which for 'lfun closures' is the object the lfun is defined in, which is not necessarily the object the closure is bound to).
    * 
    * If \p value is a struct, the \p flag setting 2 lets the efun return the base name of the struct.
    * 
    * If \p value is a lfun or context closure, the \p flag setting 3 lets the efun return the name of the program the closure was defined in. For other closures, \p flag setting 3 returns 0.
    * 
    * If \p value is a lfun or context closure, the \p flag setting 4 lets the efun return the name of the function. For other closures, \p flag setting 4 returns 0.
    * 
    * For every other \p flag setting, -1 is returned.
    * 
    * The secondary information is:
    * - for mappings the width, ie the number of data items per key.
    * - for symbols and quoted arrays the number of quotes.
    * - for closures, the (internal) closure type, as defined in <lpctypes.h>.
    * - for strings 0 for shared strings, and non-0 for others.
    * - for structs the unique identifier string
    * - -1 for all other datatypes.
    * 
    * @par misleading: This function seems to be due to frequent changes as the driver develops resp. is debugged.
    * 
    * @synopsis{
    * mixed get_type_info(mixed value)
    * mixed get_type_info(mixed value, int flag)
    * }
    * 
    * @history{
    * introduced (3.2@127) -- in the 3.2 branch, flag could be of any type
    * changed (3.2.1@84) -- added flag setting 2.
    * changed (3.2.7) -- added secondary string information.

get_type_info(closure,2) now returns the object from a lambda closure or bound-lambda closure.
    * added secondary string information.
    * get_type_info(closure,2) now returns the object from a lambda closure or bound-lambda closure.
    * changed (3.3.276) -- added the secondary information for structs.
    * changed (3.3.548) -- added flag setting '3' for lfun/context closures.
    * changed (3.3.708) -- added flag setting '4' for lfun/context closures.
    * }
    * 
    * @see efun::debug_info(), efun::typeof(), efun::to_object()
   **/
   mixed get_type_info(mixed value, int flag);
}
