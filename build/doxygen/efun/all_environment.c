public class efun {
   /**
    * Returns an array with all environments object \p obj is in. If \p obj is omitted, the environments of the current object is returned.
    * 
    * If \p obj has no environment, or if \p obj is destructed, 0 is returned.
    * 
    * @synopsis{
    * object * all_environment()
    * object * all_environment(object obj)
    * }
    * 
    * @usage{
    * If \p obj is a match in a matchbox which is in a box in a chest, in a room, `all_environment(obj)` will return `({ matchbox, box, chest, room })`.
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6) -- suggested by Tubmud.
    * }
    * 
    * @see efun::environment(), efun::all_inventory()
   **/
   object * all_environment(object obj);
}
