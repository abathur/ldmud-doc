public class efun {
   /**
    * The function returns the object which \p obj is currently shadowing, or 0 if \p obj is not a shadow.
    * 
    * @synopsis{
    * object query_shadowing(object obj)
    * }
    * 
    * @history{
    * introduced (3.2.1@73)
    * }
    * 
    * @see efun::shadow(), efun::unshadow()
   **/
   object query_shadowing(object obj);
}
