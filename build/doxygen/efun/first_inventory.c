public class efun {
   /**
    * Get the first object in the inventory of \p ob, where \p ob is either an object or the file name of an object. If \p ob is not given, the current object is assumed.
    * 
    * @synopsis{
    * object first_inventory()
    * object first_inventory(string ob)
    * object first_inventory(object ob)
    * }
    * 
    * @usage{
    * This efun is mostly used in the following context:
    * 
    * ~~~{.c}
    * for(object ob = first_inventory(container); ob; ob = next_inventory(ob)) {
    *   <some actions>
    * }
    * 
    * ~~~
    * If you use such calls frequently then it would be very useful to use a preprocessor macro:
    * 
    * ~~~{.c}
    * #define FORALL(x, y) for(x=first_inventory(y);x;x=next_inventory(x))
    * 
    * ~~~
    * So the above example could be written like this:
    * 
    * ~~~{.c}
    * FORALL(ob, container) {
    *   <some actions>
    * }
    * 
    * ~~~
    * @par warning: If the object ob is moved inside <some actions>, then efun::next_inventory() will return an object from the new inventory of ob. You also shouldn't call efun::next_inventory() on destructed objects.In case of move and/or destruction the following is a better solution:~~~{.c}
    * for(object ob = first_inventory(container); ob;) {
    *   object next = next_inventory(ob);
    *   <some actions and moves and/or removes>
    *   ob = next;
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::next_inventory(), efun::all_inventory(), efun::environment(), efun::deep_inventory()
   **/
   object first_inventory(object ob);
}
