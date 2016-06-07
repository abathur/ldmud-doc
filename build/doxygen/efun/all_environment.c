public class efun {
   /**
    * Returns an array with all environments object <o> is in. If <o> is omitted, the environments of the current object is returned.
    * 
    * If <o> has no environment, or if <o> is destructed, 0 is returned.
    * 
    * @synopsis{
    * object * all_environment()
    * object * all_environment(object o)
    * }
    * 
    * @usage{
    * If o is a match in a matchbox which is in a box in a chest, in a room, all_environment(o) will return ({ matchbox, box, chest, room }).
    * Todo
    * 
    * above could be an 'example' directive
    * }
    * 
    * @history{
    * introduced (3.2.6) -- suggested by Tubmud.
    * }
    * 
    * @see efun::environment(), efun::all_inventory()
   **/
   object * all_environment(object o);
}
