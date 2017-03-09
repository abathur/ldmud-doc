public class master {
   /**
    * Master was reloaded on external request by SIGUSR1. It will be called after master::inaugurate_master() of course. If you plan to do additional magic here, you're welcome.
    * 
    * @synopsis{
    * void external_master_reload()
    * }
    * 
    * @see master::inaugurate_master()
   **/
   void external_master_reload();
}
