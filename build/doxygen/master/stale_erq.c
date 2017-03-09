public class master {
   /**
    * Notify the loss of the erq demon. Argument is the callback closure set for an erq request.
    * 
    * If the erq connection dies prematurely, the driver will call this lfun for every pending request with set callback. This function should notify the originating object that the answer will never arrive.
    * 
    * @synopsis{
    * void stale_erq(closure callback)
    * }
    * 
    * @history{
    * introduced (3.2.1@61)
    * }
    * 
    * @see 
   **/
   void stale_erq(closure callback);
}
