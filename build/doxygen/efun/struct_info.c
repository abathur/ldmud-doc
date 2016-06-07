public class efun {
   /**
    * Return an array of information about the structure of struct <st>.
    * If <st> has a base struct, <what> determines how the information
    * is returned:
    * 
    * <what> == SINFO_FLAT:
    * All members of <st>, including those inherited from the base
    * struct, are returned on the top level of the result.
    * The base struct is signified by just its name.
    * 
    * <what> == SINFO_NESTED:
    * Only the members defined in <st> itself are returned on
    * the top level of the result. The information for the base
    * struct is an array by itself, as it would be returned
    * by a call to struct_info() for a base struct instance.
    * 
    * The elements in the resulting array are:
    * 
    * string [SI_NAME]:        the name of the struct
    * string [SI_PROG_NAME]:   the name of program defining the struct
    * string [SI_PROG_ID]:     the id of the program defining the struct
    * mixed  [SI_BASE]:        0, or the base struct information
    * mixed >>*<<[SI_MEMBER+0]:    the first member information
    * mixed >>*<<[SI_MEMBER+n]:    the last member information
    * 
    * The member information entries are arrays themselves with
    * these elements:
    * 
    * string [SIM_NAME]:  name of the member
    * int    [SIM_TYPE]:  the type of the member (compile-time value)
    * string [SIM_EXTRA]: 0, or if the member is a struct, the
    * 
    *    struct name
    *    
    * @headerfile <lpctypes.h>
    * 
    * @headerfile <struct_info.h>
    * 
    * @synopsis{
    * mixed * struct_info(struct st, int what)
    * }
    * 
   **/
   mixed * struct_info(struct st, int what);
}
