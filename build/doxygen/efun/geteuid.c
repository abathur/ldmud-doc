public class efun {
   /**
    * Get the effective user-id of the object (mostly a wizard or
    * domain name). Standard objects cloned by this object will get
    * that userid. The effective userid is also used for checking access
    * permissions. If ob is omitted, is this_object() as default.
    * 
    * @synopsis{
    * string geteuid(object ob)
    * }
    * 
   **/
   string geteuid(object ob);
}
