public class efun {
   /**
    * Enable this object to use commands normally accessible to users. This also marks the current object as "living".
    * 
    * Avoid calling this function outside of `create()` (or `reset(0)` in compat mode), because the command giver will be set to this object.
    * 
    * @synopsis{
    * void enable_commands()
    * }
    * 
    * @usage{
    * This example makes the current object a living object which then can be accessed via `find_living("dummymonster")`:
    * 
    * ~~~{.c}
    * void create() {
    *   enable_commands();
    *   set_living_name("dummymonster");
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::command(), efun::living(), efun::disable_commands(), @ref driver_hook_overview "hook"
   **/
   void enable_commands();
}
