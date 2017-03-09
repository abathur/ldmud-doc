public class efun {
   /**
    * Returns the user who currently snoops \p victim. The calling object must be privileged by the master object.
    * 
    * @synopsis{
    * object query_snoop(object victim)
    * }
    * 
    * @see efun::snoop()
   **/
   object query_snoop(object victim);
}
