public class efun {
   /**
    * Sets the option <what> to the value <data> on the interactive <ob>
    * or the default for all interactives if <ob> is 0.
    * 
    * If the first argument <ob> is not this_object(), the privilege
    * violation ("configure_interactive", this_object(), ob, what, data)
    * occurs.
    * 
    * As <what>, the following arguments are accepted:
    * 
    * <what> == IC_MAX_WRITE_BUFFER_SIZE
    * 
    * Sets the maximum amount of data to be held pending for writing
    * per player to <data> bytes. A value of -1 means unlimited,
    * 0 deactivates the write buffer.
    * 
    * @headerfile <configuration.h>
    * 
    * @synopsis{
    * void configure_interactive(object ob, int what, mixed data)
    * }
    * 
    * @history{
    * introduced (3.3.719)
    * }
    * 
    * @see efun::configure_driver()
   **/
   void configure_interactive(object ob, int what, mixed data);
}
