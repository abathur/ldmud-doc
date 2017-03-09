public class efun {
   /**
    * The item is moved into its new environment env, which may be 0. This efun is to be used in `H_MOVE_OBJECT`, as it does <em>nothing</em> beyond moving the item - no calls to applied::init() or such.
    * 
    * Don't use it in your own objects!
    * 
    * @synopsis{
    * void set_environment(object item, object env)
    * }
    * 
    * @history{
    * introduced (3.2.1@1) -- as efun308()
    * changed (3.2.6) -- renamed to set_environment
    * }
    * 
    * @see applied::remove(), applied::init(), efun::move_object(), efun::transfer(), @ref driver_hook_overview "hook"
   **/
   void set_environment(object item, object env);
}
