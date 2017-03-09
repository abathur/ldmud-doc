public class master {
   /**
    * Load the object with the given file name (which was returned by master::epilog()). It is the task of the master::epilog()/master::preload() pair to ensure the validity of the given strings (e.g. filtering out comments and blank lines). For preload itself a `call_other(file, "???")` is sufficient, but it should be guarded by a efun::catch() to avoid premature blockings. Also it is wise to change the master's euid from root_uid to something less privileged for the time of the preload.
    * 
    * You can of course do anything else with the passed strings--preloading is just the traditional task.
    * 
    * @synopsis{
    * void preload(string file)
    * }
    * 
    * @see master::epilog()
   **/
   void preload(string file);
}
