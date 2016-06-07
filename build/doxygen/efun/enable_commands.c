public class efun {
   /**
    * Enable this object to use commands normally accessible to
    * users. This also marks the current object as "living".
    * 
    * Avoid to call this function from other places then from inside
    * create() (or reset(0) in compat mode), because the command
    * giver will be set to this object.
    * 
    * @synopsis{
    * void enable_commands()
    * }
    * 
    * @usage{
    * void create() {
    * 
    * enable_commands();
    * set_living_name("dummymonster");
    * }
    * This will make the current object a living object which then
    * can be accessed via find_living("dummymonster").
    * }
    * 
    * @see efun::command(), efun::living(), efun::disable_commands(), @ref driver_concepts_native "native"
   **/
   void enable_commands();
}
