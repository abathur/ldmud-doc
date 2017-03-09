public class efun {
   /**
    * Get the effective user-id of the object (mostly a wizard or domain name). Standard objects cloned by this object will get that userid. The effective userid is also used for checking access permissions. If \p ob is omitted, is `this_object()` as default.
    * 
    * @synopsis{
    * string geteuid(object ob)
    * }
    * 
    * @history{
    * changed (3.2.1@47) -- this efun is availabe only when using euids.
    * changed (3.2.7) -- this efun is always available.
    * }
    * 
    * @see efun::seteuid(), efun::getuid(), efun::export_uid()
   **/
   string geteuid(object ob);
}
