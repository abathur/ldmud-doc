public class applied {
   /**
    * In compat mode, this function is used by efun::transfer().
    * 
    * Define this function in objects that are neither living nor rooms if you want to prevent to put something into current object.
    * 
    * Return true if ok, otherwise 0. That means that default is that it is not possible to put something into an object.
    * 
    * @synopsis{
    * int prevent_insert()
    * }
    * 
    * @history{
    * deprecated (3.3) -- because transfer() has been deprecated.
    * }
    * 
    * @see efun::transfer(), applied::can_put_and_get()
   **/
   int prevent_insert();
}
