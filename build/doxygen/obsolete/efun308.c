public class efun {
   /**
    * The item is moved into its new environment env, which may be 0.
    * This efun is to be used in the move_object() hook, as it does
    * nothing else than moving the item - no calls to init() or such.
    * 
    * Don't use it in your own objects!
    * 
    * @synopsis{
    * void efun308(object item, object env)
    * }
    * 
    * @history{
    * introduced (3.2.1@1)
    * changed (3.2.6) -- renamed to set_environment()
    * changed (3.2.9) -- not available if driver is compiled without USE_DEPRECATED.
    * removed (3.3)
    * }
    * 
    * @see applied::remove(), applied::init(), efun::move_object(), efun::transfer(), @ref driver_concepts_native "native"
   **/
   void efun308(object item, object env);
}
