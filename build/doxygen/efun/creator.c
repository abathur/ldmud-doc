public class efun {
   /**
    * This efun is for backward compatibility only. It is only available in compat mode.
    * 
    * Returns the creator (i.e. the name of the wizard or domain) of the object. Default for \p ob is `this_object()`.
    * 
    * @synopsis{
    * string creator(object ob)
    * }
    * 
    * @history{
    * changed (3.2.1@47) -- this efun is now an alias for getuid.
    * }
    * 
    * @see efun::getuid()
   **/
   string creator(object ob);
}
