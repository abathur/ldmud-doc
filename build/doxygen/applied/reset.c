public class applied {
   /**
    * The @ref driver_hook_reset "H_RESET" hook defines the function or closure to be called when the driver needs to reset an object. In older drivers this was hardwired to the lfun applied::reset(), and a lot of hook implementations still follow this tradition.
    * 
    * In compat mode, applied::reset() was called with arg 0 after the object was compiled, and with arg != 0 every once in a while. In native mode, applied::create() is called after compiling, and applied::reset() is called without arguments every once in a while.
    * 
    * So, if the argument is zero, the parser is running in compat mode, and applied::reset() may call your applied::create() code. If applied::create() is called, you're on the new version and applied::reset() is not called for object creation. You may call applied::reset() from applied::create() and vice versa, but make sure they do not call each other recursively on either type of driver.
    * 
    * applied::reset() will be called only in objects that have been used since the last call to applied::reset(), i.e. a function in them was called (other than applied::reset() or applied::clean_up()), or it was moved around.
    * 
    * This function can be used to reset the state of the object or do some checks or what ever. The game wouldn't be fun if no challenges remained.
    * 
    * @synopsis{
    * void reset(int arg)
    * void reset(void)
    * }
    * 
    * @history{
    * changed (3.2.1) -- the mudlib can be programmed to call an other lfun than reset to reset an object with reset
    * }
    * 
    * @see applied::clean_up(), applied::heart_beat(), efun::call_out(), applied::create(), applied::__INIT(), @ref driver_hook_reset "reset", @ref driver_hook_overview "hook", @ref driver_master_initialisation "initialisation"
   **/
   void reset(void);
}
