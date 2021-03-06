public class efun {
   /**
    * All commands for the current object (which must interactive) will be passed to `ob->modify_command()` before actually being executed. The argument can be passed an object or an object_name.
    * 
    * When efun::set_modify_command() was called, the parser won't expand the standard abbreviations (n,e,s,w,nw,sw,ne,se) for that user anymore, nor use any hook set for this.
    * 
    * - 0 as argument will stop the command modification and reinstall the standard abbreviations.
    * - -1 as argument will just return the object previously set.
    * 
    * The return value is the object that was previously set with efun::set_modify_command(), if any.
    * 
    * This mechanism is intended to expand aliases on quicktypers or the like. The name of the lfun called can be changed from >>:apply:`modify_command`<< to something else using the @ref driver_hook_modify_command_fname "H_MODIFY_COMMAND_FNAME" hook.
    * 
    * Up to @subpage driver_mailto:3.2.1@108 "3.2.1@108" the lfun called was hardcoded as 'modify_command'. The hook @ref driver_hook_modify_command_fname "H_MODIFY_COMMAND_FNAME" introduced
    * in @subpage driver_mailto:3.2.1@109 "3.2.1@109" allows to change the name.
    * 
    * @synopsis{
    * object set_modify_command(object)
    * object set_modify_command(string)
    * object set_modify_command(int)
    * }
    * 
    * @see efun::command(), @ref driver_hook_overview "hook", applied::modify_command()
   **/
   object set_modify_command(int);
}
