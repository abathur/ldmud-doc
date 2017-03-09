public class master {
   /**
    * Handle quotas in times of memory shortage.
    * 
    * This function is called during the final phase of a garbage collection if the reserved user area couldn't be reallocated. This function (or a called demon) has now the opportunity to remove some (still active) objects from the system. If this does not free enough memory to reallocate the user reserve, master::slow_shut_down() will be called to start Armageddon.
    * 
    * Up to now, the wizlist lacks various information needed to detect the memory-hungriest users.
    * 
    * @synopsis{
    * void quota_demon(void)
    * }
    * 
    * @see master::slow_shut_down()
   **/
   void quota_demon(void);
}
