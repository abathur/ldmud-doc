public class efun {
   /**
    * This function is for system internal use and should never be called by
    * user objects. It is supposed to check the stack integrity and aborts
    * the driver when it detects corruption.
    * 
    * @synopsis{
    * void break_point()
    * }
    * 
    * @see efun::shutdown(), efun::swap()
   **/
   void break_point();
}
