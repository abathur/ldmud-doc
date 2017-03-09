public class efun {
   /**
    * If ob is interactive and currently has an efun::input_to() pending, the object that has called the efun::input_to() is returned, else 0.
    * 
    * @synopsis{
    * object query_input_pending(object ob)
    * }
    * 
    * @see efun::input_to(), efun::find_input_to(), efun::input_to_info(), efun::remove_input_to()
   **/
   object query_input_pending(object ob);
}
