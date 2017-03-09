public class efun {
   /**
    * Returns an array of the objects contained in the inventory of \p ob, or of `this_object()`, if no arg given.
    * 
    * @synopsis{
    * object * all_inventory()
    * object * all_inventory(object ob)
    * }
    * 
    * @see efun::first_inventory(), efun::next_inventory(), efun::deep_inventory(), efun::all_environment(), efun::environment()
   **/
   object * all_inventory(object ob);
}
