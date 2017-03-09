public class efun {
   /**
    * Sets the option \p what to the value \p data on the interactive \p ob or the default for all interactives if \p ob is 0.
    * 
    * If the first argument \p ob is not `this_object()`, the privilege violation ("configure_interactive", this_object(), ob, what, data) occurs.
    * 
    * As \p what, the following arguments are accepted:
    * 
    * \p what == `IC_MAX_WRITE_BUFFER_SIZE`
    * Sets the maximum amount of data to be held pending for writing per player to \p data bytes. A value of -1 means unlimited, 0 deactivates the write buffer.
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
