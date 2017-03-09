public class master {
   /**
    * Remove an interactive user object ob from the system. This function is called by the interpreter to expell remaining users from the system on shutdown in a polite way. If this functions fails to quit/destruct the user, he will be destructed the hard way by the interpreter.
    * 
    * This function must not cause runtime errors.
    * 
    * @synopsis{
    * void remove_player(object ob)
    * }
    * 
    * @see efun::remove_interactive(), master::slow_shut_down()
   **/
   void remove_player(object ob);
}
