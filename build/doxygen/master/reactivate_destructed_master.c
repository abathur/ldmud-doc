public class master {
   /**
    * This function is called in an already destructed master object if no new master object could be loaded. flag will be 1 if the old master object could be reclaimed from the list of objects that were marked for destruction but not yet terminated. If flag is 0, all variables of the object have been set to 0 and must be re-initialized.
    * 
    * After this function, master::inaugurate_master() will be applied again.
    * 
    * @synopsis{
    * void reactivate_destructed_master(int flag)
    * }
    * 
    * @see efun::destruct(), master::inaugurate_master()
   **/
   void reactivate_destructed_master(int flag);
}
