public class efun {
   /**
    * Get next object in the same inventory as ob. If ob is not given, the current object will be used.
    * 
    * This efun is mostly used together with the efun efun::first_inventory().
    * 
    * @synopsis{
    * object next_inventory()
    * object next_inventory(object ob)
    * }
    * 
    * @see efun::first_inventory(), efun::all_inventory(), efun::environment(), efun::deep_inventory()
   **/
   object next_inventory(object ob);
}
