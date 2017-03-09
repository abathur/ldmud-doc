public class efun {
   /**
    * Return the max number of commands the interactive \p obj is allowed to execute per second. A negative result means 'unlimited'.
    * 
    * If \p obj is not given, the current interactive is queried. For non-interactive objects the result is 0.
    * 
    * A 'command' in this context means every received data packet which causes a LPC call - actions and calls to efun::input_to() alike.
    * 
    * @synopsis{
    * int get_max_commands()
    * int get_max_commands(object obj)
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see efun::set_max_commands()
   **/
   int get_max_commands(object obj);
}
