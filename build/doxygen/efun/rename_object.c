public class efun {
   /**
    * Give the object <ob> a new object name <new_name>. Causes a privilege
    * violation. The new name must not contain a # character, except
    * at the end, to avoid confusion with clone numbers.
    * 
    * @synopsis{
    * void rename_object(object ob, string new_name)
    * }
    * 
    * @history{
    * introduced (3.2@55)
    * }
    * 
    * @see efun::creator(), efun::object_name(), efun::load_name()
   **/
   void rename_object(object ob, string new_name);
}
