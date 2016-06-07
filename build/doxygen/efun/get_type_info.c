public class efun {
   /**
    * Returns info about the type of arg, as controlled by the flag.
    * 
    * If the optional argument <flag> is not given, an array is
    * returned whose first element is an integer denoting the data
    * type, as defined in <lpctypes.h>. The second entry can contain
    * additional information about arg.
    * 
    * If <flag> flag is the number 0, only the first element of that array
    * (i.e. the data type) is returned (as int). If <flag> is 1, the
    * second element is returned.
    * 
    * If <arg> is a closure, the <flag> setting 2 lets the efun
    * return the object of the closure (which for 'lfun closures' is
    * the object the lfun is defined in, which is not necessarily the object
    * the closure is bound to).
    * 
    * If <arg> is a struct, the <flag> setting 2 lets the efun
    * return the base name of the struct.
    * 
    * If <arg> is a lfun or context closure, the <flag> setting 3 lets the
    * efun return the name of the program the closure was defined in. For
    * other closures, <flag> setting 3 returns 0.
    * 
    * If <arg> is a lfun or context closure, the <flag> setting 4 lets the
    * efun return the name of the function. For other closures, <flag>
    * setting 4 returns 0.
    * 
    * For every other <flag> setting, -1 is returned.
    * 
    * The secondary information is:
    * - for mappings the width, ie the number of data items per key.
    * - for symbols and quoted arrays the number of quotes.
    * - for closures, the (internal) closure type, as defined in
    *   <lpctypes.h>.
    * - for strings 0 for shared strings, and non-0 for others.
    * - for structs the unique identifier string
    * - -1 for all other datatypes.
    * 
    * BUGS
    * This function seems to be due to frequent changes as the
    * driver develops resp. is debugged.
    * 
    * @synopsis{
    * mixed get_type_info(mixed arg)
    * mixed get_type_info(mixed arg, int flag)
    * }
    * 
   **/
   mixed get_type_info(mixed arg, int flag);
}
