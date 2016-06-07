public class applied {
   /**
    * This function was used in compat mode drivers in context with moving objects. Nowadays objects are moved by means of the @ref driver_hook_move_object "move_object" hooks, and use of this lfun is up to the mudlib.
    * 
    * This function was called in the old environment everytime a living object ob leaves it.
    * 
    * efun::this_player() will return a random value, don't use it at this point.
    * 
    * @par warning:An error in this function will leave the player stranded in the current room until the next reboot.
    * 
    * @synopsis{
    * void exit(object ob)
    * }
    * 
    * @see applied::init()
   **/
   void exit(object ob);
}
