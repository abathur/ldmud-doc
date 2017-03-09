public class applied {
   /**
    * Does some housekeeping to ensure consistency and then destructs the current object.
    * 
    * This lfun is not applied by the parser, but by other objects to tell the current object to self-destruct. applied::remove() should be supplied by the base classes of the library. Return 1 if actually self-destructed, 0 otherwise.
    * 
    * An alternative way to ensure the housekeeping on destruction is through the use of master::prepare_destruct().
    * 
    * @par note: Your actual mudlib may name this lfun differently, "remove" is just the traditional name.
    * 
    * @synopsis{
    * int remove(void)
    * }
    * 
    * @see efun::destruct(), master::prepare_destruct()
   **/
   int remove(void);
}
