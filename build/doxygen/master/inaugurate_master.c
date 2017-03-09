public class master {
   /**
    * This function is called in the master object after it has been created and is fully functional.
    * 
    * @par note: The applied::create() function is of little use in constructing the master object because there is no simul_efun object yet and the interpreter does not know anything about the user-ids and access permissions.
    * 
    * The argument \p arg denotes why this function is called:
    * 
    * arg = 0
    * the mud just started, this is the first master of all.
    * 
    * arg = 1
    * the master was destructed and then reactivated (because a new one couldn't be loaded).
    * 
    * arg = 2
    * the master was destructed and then reactivated, but additionally lost all variable contents.
    * 
    * arg = 3
    * this is a reloaded master.
    * 
    * This function has to at least set up the driverhooks to use (in 3.2.1). Also, any mudwho or wizlist handling has to be initialized here.
    * 
    * Besides that, do whatever you feel you need to do, e.g. `set_auto_include_string()`, or give the master a decent euid.
    * 
    * @synopsis{
    * void inaugurate_master(int arg)
    * }
    * 
    * @see applied::create(), master::get_master_uid(), master::flag(), master::reactivate_destructed_master()
   **/
   void inaugurate_master(int arg);
}
