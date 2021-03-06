public class master {
   /**
    * Load the simul_efun object(s) and return one or more paths of it.
    * 
    * Note that the object(s) must be loaded by this function!
    * 
    * When you return an array of strings, the first string is taken as path to the simul_efun object, and all other paths are used for backup simul_efun objects to call simul_efuns that are not present in the main simul_efun object. This allows the removal of simul_efuns at runtime without getting errors from old compiled programs that still use the obsolete simul_efuns.
    * 
    * The additional simul-efun objects can not serve as backups for the primary one!
    * 
    * @synopsis{
    * string|string* get_simul_efun(void)
    * }
    * 
    * @see 
   **/
   string|string* get_simul_efun(void);
}
