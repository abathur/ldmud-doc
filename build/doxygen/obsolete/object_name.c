public class master {
   /**
    * Return a printable name for an object. This function is called
    * by sprintf() to print a meaningful name in addition to the
    * normal object_name().
    * 
    * @synopsis{
    * string object_name(object ob)
    * }
    * 
    * @history{
    * changed (3.2.6) -- renamed to printf_obj_name() due to the introduction
of an efun with this name.
    * }
    * 
    * @see efun::sprintf(), master::printf_obj_name(), efun::object_name()
   **/
   string object_name(object ob);
}
