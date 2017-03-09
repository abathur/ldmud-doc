public class efun {
   /**
    * Set the max number of commands the interactive \p obj is allowed to execute per second to \p num. A negative value means 'unlimited' and is the setting for newly created connections.
    * 
    * If \p obj is not given, the current interactive is queried.
    * 
    * The function raises a privilege_violation ("set_max_commands", obj, num). If the privilege is denied, the call is ignored.
    * 
    * A 'command' in this context means every received data packet which causes a LPC call - actions and calls to efun::input_to() alike.
    * 
    * @synopsis{
    * void set_max_commands(int num)
    * void set_max_commands(int num, object obj)
    * }
    * 
    * @usage{
    * To establish a mud-wide default for the maximum command rate, write master::connect() like this:
    * 
    * ~~~{.c}
    * object connect() {
    *   object obj;
    * 
    *   ...
    *   set_max_commands(100);
    *   return obj;
    * }
    * 
    * ~~~
    * Upon return from the the function, the connection with its modified max_commands will be re-bound from the master object to the returned object.
    * 
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see efun::get_max_commands(), master::privilege_violation()
   **/
   void set_max_commands(int num, object obj);
}
