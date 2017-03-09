public class master {
   /**
    * Return a printable name for an object. This function is called by efun::sprintf() to print a meaningful name in addition to the normal efun::object_name().
    * 
    * @synopsis{
    * string printf_obj_name(object ob)
    * }
    * 
    * @history{
    * changed (3.2.6) -- renamed to printf_obj_name() from object_name() due to the introduction of object_name.
    * }
    * 
    * @see efun::sprintf(), efun::object_name()
   **/
   string printf_obj_name(object ob);
}
