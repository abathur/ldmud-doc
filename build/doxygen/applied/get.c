public class applied {
   /**
    * In compat mode, this function is used by efun::transfer().
    * 
    * If an object wants control over when it is possible to pick it up (i.e. moved into a living object) it must define applied::get(), and return 1 if ok to pick up.
    * 
    * @par note: applied::id() has been called before this to identify the object.
    * 
    * @synopsis{
    * int get()
    * }
    * 
    * @history{
    * deprecated (3.3) -- because transfer has been deprecated.
    * }
    * 
    * @see efun::transfer(), applied::drop()
   **/
   int get();
}
