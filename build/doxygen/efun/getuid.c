public class efun {
   /**
    * User-ids are not used in compat mode. Get user-id of the object, i.e. the name of the wizard or domain that is responsible for the object. This name is also the name used in the wizlist. If no \p ob is given, use `this_object()` as default.
    * 
    * @synopsis{
    * string getuid(object ob)
    * }
    * 
    * @history{
    * changed (3.2.1@47) -- creator is an alias for this efun
    * }
    * 
    * @see efun::seteuid(), efun::geteuid(), efun::export_uid(), efun::creator()
   **/
   string getuid(object ob);
}
