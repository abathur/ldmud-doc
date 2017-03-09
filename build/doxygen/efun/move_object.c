public class efun {
   /**
    * The item, which can be an object_name or an object, is moved into it's new environment dest, which can also be an object_name or an object.
    * 
    * @par note: For !compat mode, the traditional implementation required \p item to be the calling object.
    * 
    * @synopsis{
    * void move_object(mixed item, mixed dest)
    * }
    * 
    * @history{
    * changed (3.2.1) -- the innards of move_object() are implemented in the mudlib, using the M_MOVE_OBJECT0/1 driver hooks, and move_object() might as well be an simul-efun
    * }
    * 
    * @see applied::remove(), applied::init(), efun::transfer(), @ref driver_hook_overview "hook", efun::set_environment()
   **/
   void move_object(mixed item, mixed dest);
}
