public class applied {
   /**
    * @ref driver_hook_move_object "move_object" implements the details of moving objects. In older drivers, applied::init() was called to handle the adding of actions, and a lot of hook implementations still follow this tradition.
    * 
    * The main purpose of this function is to publish the commands an object implements to other, living objects. Traditionally, whenever a living object enters the vicinity of another object, applied::init() is called in the latter and efun::this_player() will point to the former object. This happens mutually should both objects happen to be living.
    * 
    * Or more formally:
    * 
    * - If the object O that moves is marked as living then first call applied::init() of the destination object D with efun::this_player() set to O.
    * - Then apply the two following rules for each object C inside D:
    * - If C is marked as living then call `O->init()` with `this_player()` set to C.
    * - If O is marked as living then call `C->init()` with `this_player()` set to O.
    * - Finally, if D is marked as living then call `O->init()`, with efun::this_player() set to D.
    * 
    * @par warning: commands defined in the player object for the player should not be defined in applied::init(), as these commands would be added to _other_ players whenever they happen to be nearby. Instead use a separate function (`add_player_commands()` or so) which is called during the creation of the player.
    * 
    * @synopsis{
    * void init()
    * }
    * 
    * @usage{
    * (This example assumes a traditional implementation of the movement handling)
    * 
    * Lets say we have a object structure of living (l1 and l2) and non living objects (n1 and n2) as the following:
    * 
    * - l1
    * - n1
    * - l2
    * - n2
    * 
    * If we now move another living object l3 into l1, the call sequence of the `init()` functions looks like this:
    * 
    * ~~~{.c}
    * l1->init()  //first init() of the destination will be called
    * n1->init()  //now iterate through the inventory of the destination
    * l3->init()
    * l2->init()
    * n2->init()
    * l3->init()  //finally call init() of the object that has been moved
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.1) -- the actual move handling became part of the object library, so a given installation may implement any other scheme of calling init.
    * }
    * 
    * @see efun::add_action(), efun::set_environment(), efun::environment(), efun::move_object(), @ref driver_hook_overview "hook"
   **/
   void init();
}
