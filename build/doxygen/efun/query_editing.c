public class efun {
   /**
    * Returns 1 if the ob is interactive and currently editing
    * with ed(). If ed() was called with a function name as
    * second argument, the object where ed() was called is returned,
    * else 0.
    * 
    * @synopsis{
    * mixed query_editing(object ob)
    * }
    * 
    * @see efun::ed()
   **/
   mixed query_editing(object ob);
}
