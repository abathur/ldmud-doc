include_dirs {#driver_hook_include_dirs}
========================================
Semi-mandatory hook specifying the directories where @a<>`-type include files are searched (this includes @a""`-includes not found as specified). Hook setting may be any closure or a string array. If not set, only @a""`-type includes may be used in LPC programs.

The hook is called only if a call to master::include_file() does not return a usable filename.

If the hook setting is a string array, it has to contain the path names of those directories where @a<>`-type includes are to be searched. The directories are searched in the order they appear in the array. The directory name and the name of the actual include file are concatenated, therefore the directory names have to end in @a/`. Leading slashes may be omitted.

If the setting is a closure, it is called with the name of the desired include file as first, and the name of the compiled LPC file as second argument. Result has to be the complete path name of the include file to use. Leading slashes may be omitted. If the closure is a lambda closure, it is bound to this_object() prior to execution.

@headerfile <sys/driver_hooks.h>

@synopsis{
set_driver_hook(H_INCLUDE_DIRS, value)
}

@see @ref driver_hook_auto_include "auto_include", master::include_file()
Arguments: 
- value (@ref driver_LPC_string "string*") -- <dirs>
- value (@ref driver_LPC_closures "closure") -- string <closure>(string include_name, string current_file)
