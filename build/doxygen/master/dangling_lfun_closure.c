public class master {
   /**
    * Handle a dangling lfun-closure.
    * 
    * This is called when the gamedriver executes a closure using a vanished lfun, with `previous_object()` showing the originating object. A proper handling is to raise a runtime error.
    * 
    * # Technical #
    * 
    * Upon replacing programs (see efun::replace_program()), any existing lambda closures of the object are adjusted to the new environment. If a closure uses a lfun which vanished in the replacement process, the reference to the lfun is replaced by an alien-lfun closure referencing to this function. The error will then occur when the execution of the adjusted lambda reaches the point of the lfun reference. There are two reasons for the delayed handling. First is that the program replacement and with it the closure adjustment happens at the end of a backend cycle, outside of any execution thread: noone would see the error at this time. Second, smart closures might know/recognize the program replacement and skip the call to the vanished lfun.
    * 
    * @synopsis{
    * void dangling_lfun_closure()
    * }
    * 
    * @history{
    * changed (3.2.9) -- all references to dangling_lfun_closure are now created as alien-lfun closures.
    * }
    * 
    * @see @ref driver_syntax_closures "closure"
   **/
   void dangling_lfun_closure();
}
