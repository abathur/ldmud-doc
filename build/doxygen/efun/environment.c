public class efun {
   /**
    * Returns the surrounding object of obj, which may be given by name. If no argument is given, it returns the surrounding of the current object.
    * 
    * Destructed objects do not have an environment.
    * 
    * @synopsis{
    * object environment(void)
    * object environment(object obj)
    * object environment(string obj)
    * }
    * 
    * @usage{
    * This will return the current room you are in:
    * 
    * ~~~{.c}
    * object room;
    * room = environment(this_player());
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::first_inventory(), efun::next_inventory(), efun::all_inventory(), efun::all_environment()
   **/
   object environment(string obj);
}
