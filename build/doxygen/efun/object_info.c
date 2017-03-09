public class efun {
   /**
    * Returns some internal information about object \p ob, collected in an array. Argument \p what determines which information is returned.
    * 
    * The result is usually an array. However, if \p index is specified, the result is the value from position \p index of the array which would have been returned normally.
    * 
    * Caution: The possible values of \p what, and the indices of the returned arrays are defined in the include file <objectinfo.h>, and may change in future versions of the driver!
    * \p what == `OINFO_BASIC`:
    * 
    * This call returns basic information about \p ob:
    * 
    * int [`OIB_HEART_BEAT`]:       1 if \p ob has a heart_beat, 0 else.
    * int [`OIB_IS_WIZARD`]:        1 if \p ob has the wizard flag set, 0 else. This entry is always 0 when efun::set_is_wizard() is not available.
    * int [`OIB_ENABLE_COMMANDS`]:  1 if \p ob can give commands, 0 else.
    * int [`OIB_CLONE`]:            1 if \p ob is a clone, 0 else.
    * int [`OIB_DESTRUCTED`]:       1 if \p ob is destructed, 0 else.
    * int [`OIB_SWAPPED`]:          1 if \p ob is swapped, 0 else.
    * int [`OIB_ONCE_INTERACTIVE`]: 1 if \p ob was once interactive, 0 else.
    * int [`OIB_RESET_STATE`]:      1 if \p ob is (still) reset, 0 else.
    * int [`OIB_WILL_CLEAN_UP`]:    1 if \p ob will call applied::clean_up(), 0 else.
    * int [`OIB_LAMBDA_REFERENCED`]: 1 if \p ob has lambdas, 0 else.
    * int [`OIB_SHADOW`]:           1 if \p ob has a shadow structure tied to it, 0 if not.
    * int [`OIB_REPLACED`]:         1 if the program for \p ob was replaced, 0 else.
    * int [`OIB_NEXT_RESET`]:   time of the next reset
    * int [`OIB_TIME_OF_REF`]:  time of the last call to \p ob
    * int [`OIB_NEXT_CLEANUP`]: time of the next data cleanup
    * int [`OIB_REF`]:          number of references to \p ob
    * int [`OIB_GIGATICKS`] and [`OIB_TICKS`]: together, these numbers give the accumulated evaluation cost spend in \p ob
    * int [`OIB_SWAP_NUM`]:     the swap number for \p ob program, or -1 if not swapped.
    * int [`OIB_PROG_SWAPPED`]: 1 if \p ob's program is swapped, 0 else.
    * int [`OIB_VAR_SWAPPED`]:  1 if \p ob's variables are swapped, 0 else.
    * int [`OIB_NAME`]:         \p ob's object name.
    * int [`OIB_LOAD_NAME`]:    \p ob's load name.
    * object [`OIB_NEXT_ALL`]:  next object in the object list.
    * object [`OIB_PREV_ALL`]:  previous object in the object list.
    * 
    * \p what == `OINFO_POSITION`:
    * 
    * This call returns information about \p ob's position in the
    * global list of objects:
    * 
    * object [`OIP_NEXT`]: next object in the object list.
    * object [`OIP_PREV`]: previous object in the object list.
    * int    [`OIP_POS`]:  position of \p ob in list, counting from 0 up.
    * 
    * This call can be expensive in computing time.
    * 
    * \p what == `OINFO_MEMORY`:
    * 
    * This call returns information about the program \p ob uses:
    * 
    * int    [`OIM_REF`]:            number of references to the program.
    * string [`OIM_NAME`]:           name of program.
    * int    [`OIM_PROG_SIZE`]:      size of the program.
    * int    [`OIM_NUM_FUNCTIONS`]:  number of functions in the program.
    * int    [`OIM_SIZE_FUNCTIONS`]: size needed for the function structs.
    * int    [`OIM_NUM_VARIABLES`]:  number of variables in the program.
    * int    [`OIM_SIZE_VARIABLES`]: size needed for the variable structs.
    * int    [`OIM_NUM_STRINGS`]:    number of strings in the program.
    * int    [`OIM_SIZE_STRINGS`]:   size needed for the string pointers.
    * int    [`OIM_SIZE_STRINGS_DATA`]: size needed for the string data, scaled down according to the extend of data sharing.
    * int    [`OIM_SIZE_STRINGS_TOTAL`]: unmodified size needed for the string data.
    * int    [`OIM_NUM_INCLUDES`]:   number of included files in the program.
    * int    [`OIM_NUM_INHERITED`]:  number of inherited programs.
    * int    [`OIM_SIZE_INHERITED`]: size needed for the inherit structs.
    * int    [`OIM_TOTAL_SIZE`]:     total size of the program.
    * int    [`OIM_DATA_SIZE`]:      total size of the values held in the object's variables, scaled down according to the extend of data sharing.
    * int    [`OIM_DATA_SIZE_TOTAL`]: unmodified total size of the values held in the object's variables
    * int    [`OIM_NO_INHERIT`]:     1 if the program can't be inherited.
    * int    [`OIM_NO_CLONE`]:       1 if the program/blueprint can't be cloned.
    * int    [`OIM_NO_SHADOW`]:      1 if the program's functions can't be shadowed.
    * int    [`OIM_SHARE_VARIABLES`]:  1 if clones of this program share their initial variable values with the blueprint.
    * 
    * This call swaps in the program if necessary.
    * 
    * @par note: The `OIM_SIZE_xxx` entries only give the size spent on the structures and pointers, not the size of the variable data, function code, and strings themselves.
    * 
    * @headerfile <objectinfo.h>
    * 
    * @synopsis{
    * mixed * object_info(object ob, int what)
    * mixed * object_info(object ob, int what, int index)
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * changed (3.2.7) -- new basic result OIB_REPLACED.

basic result OIB_IS_WIZARD is always 0 if set_is_wizard is not available.

basic result OIB_APPROVED is gone.
    * new basic result OIB_REPLACED.
    * basic result OIB_IS_WIZARD is always 0 if set_is_wizard is not available.
    * basic result OIB_APPROVED is gone.
    * changed (3.2.8) -- added OIM_DATA_SIZE to the result of OINFO_MEMORY.
    * changed (3.2.9) -- added the index mechanism, OIM_NUM_INCLUDES, OIM_NO_INHERIT, OIM_NO_SHADOW, OIM_NO_CLONE, OIM_SIZE_STRINGS_DATA, OIM_SIZE_STRINGS_TOTAL, and OIM_DATA_SIZE_TOTAL to the result of OINFO_MEMORY.
    * changed (3.3.378) -- added the OIM_SHARE_VARIABLES to the result of OINFO_MEMORY.
    * changed (3.3.654) -- added the OIB_NEXT_CLEANUP to the result of OINFO_BASIC.
    * }
    * 
    * @see efun::debug_info()
   **/
   mixed * object_info(object ob, int what, int index);
}
