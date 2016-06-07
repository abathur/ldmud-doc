public class efun {
   /**
    * The item is moved into its new environment env, which may be 0.
    * This efun is to be used in the move_object() hook, as it does
    * nothing else than moving the item - no calls to init() or such.
    * 
    * Don't use it in your own objects!
    * 
    * history 3.2.1@1 introduced: 
    *    as `efun308()`
    *    
    * history 3.2.6 renamed: 
    *    renamed to `set_environment()`
    *    
    * See Also: 
    *    applied::remove(), applied::init(), efun::move_object(), efun::transfer(), `hooks`,
    *    
    * @ref driver_concepts_native "native"
    * 
    * @synopsis{
    * void set_environment(object item, object env)
    * }
    * 
   **/
   void set_environment(object item, object env);
}
