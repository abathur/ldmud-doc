public class efun {
   /**
    * Returns an array of the objects contained in the inventory of
    * ob (or this_object() if no arg given) and in the inventories
    * of these objects, climbing down recursively.
    * 
    * If <depth> is given and not 0, the result is limited as follows:
    * 
    * <depth> > 0: Only the objects in the first <depth> levels of
    *    inventory are returned.
    *    
    * <depth> < 0: Only the objects in level -<depth> of inventory are
    *    returned.
    *    
    * In this, level '1' is the inventory of <ob> itself.
    * 
    * @synopsis{
    * object * deep_inventory(void)
    * object * deep_inventory(object ob)
    * object * deep_inventory(object ob, int depth)
    * }
    * 
    * @usage{
    * Given the following inventory structure
    * ob
    * +- ob1
    * +- ob2
    * |   `- ob21
    * |  ob3
    * |   `- ob31
    * +- ob4
    * deep_inventory(ob)     => ({ob1, ob2, ob3, ob4, ob21, ob31})
    * deep_inventory(ob, 1)  => ({ob1, ob2, ob3, ob4})
    * deep_inventory(ob, 2)  => ({ob1, ob2, ob3, ob4, ob21, ob31})
    * deep_inventory(ob, -2) => ({ob21, ob31})
    * }
    * 
    * @history{
    * changed (3.3.554) -- added the <depth> parameter
    * }
    * 
    * @see efun::first_inventory(), efun::next_inventory(), efun::all_inventory()
   **/
   object * deep_inventory(object ob, int depth);
}
