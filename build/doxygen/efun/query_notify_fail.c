public class efun {
   /**
    * If \p flag is not given or 0: return the string or closure which was last set as error message for this command (with efun::notify_fail()).
    * 
    * If \p flag is given and 1: return the object which issued the last efun::notify_fail().
    * 
    * If nothing was set yet, return 0.
    * 
    * @synopsis{
    * mixed query_notify_fail()
    * mixed query_notify_fail(int flag)
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.2.8) -- added the flag parameter.
    * }
    * 
    * @see efun::add_action(), efun::query_verb(), efun::query_command(), efun::notify_fail(), @ref driver_hook_overview "hook"
   **/
   mixed query_notify_fail(int flag);
}
