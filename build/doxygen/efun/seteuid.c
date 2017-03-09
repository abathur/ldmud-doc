public class efun {
   /**
    * Set effective uid to \p str. The calling object must be privileged to do so by the master object. In most installations it can always be set to the current uid of the object, to the uid of the creator of the object file, or to 0.
    * 
    * Result is 0 if the euid could not be changed, and non-0 if it was changed.
    * 
    * When this value is 0, the current object's uid can be changed by efun::export_uid(), and only then.
    * 
    * If strict euid usage is enforced, objects with euid 0 cannot load or clone other objects.
    * 
    * @synopsis{
    * int seteuid(string str)
    * }
    * 
    * @history{
    * changed (3.2.1@47) -- this efun is availabe only when using euids.
    * changed (3.2.7) -- this efun is always available.
    * }
    * 
    * @see efun::export_uid(), efun::getuid(), efun::geteuid(), master::valid_seteuid()
   **/
   int seteuid(string str);
}
