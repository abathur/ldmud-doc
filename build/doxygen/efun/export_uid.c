public class efun {
   /**
    * Set the uid of object \p ob to the current object's effective uid. It is only possible when object \p ob has an effective uid of 0.
    * 
    * @synopsis{
    * void export_uid(object ob)
    * }
    * 
    * @history{
    * changed (3.2.1@47) -- this efun is availabe only when using euids.
    * changed (3.2.7) -- this efun is now always available.
    * }
    * 
    * @see efun::seteuid(), efun::getuid(), efun::geteuid()
   **/
   void export_uid(object ob);
}
