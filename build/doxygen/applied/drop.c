public class applied {
   /**
    * In compat mode this lfun is used by efun::transfer().
    * 
    * It is called to check if an object wants to be moved out of the inventory of a living object. @adrop()` should return 1 to prevent dropping. This is the opposite of the @aget()` function. That is because if @adrop()` is not defined, it will always be possible to drop an object.
    * 
    * If the object self-destructs when @adrop()` is called, be sure to return 1, as the destructed item surely not can be dropped.
    * 
    * Most compat mode LPC libraries to define one argument for drop. If silently is true, no messages should be written.
    * 
    * @synopsis{
    * int drop(void)
    * int drop(int silently)
    * }
    * 
    * @history{
    * deprecated (3.3) -- because transfer() has been deprecated.
    * }
    * 
    * @see efun::transfer()
   **/
   int drop(int silently);
}
