public class efun {
   /**
    * Returns the master object.
    * 
    * If \p dont_load is false, the function first makes sure that the master object exists.
    * 
    * If \p dont_load is true, the function just returns the current master object, or 0 if the current master has been destructed.
    * 
    * @synopsis{
    * object master()
    * object master(int dont_load)
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see 
   **/
   object master(int dont_load);
}
