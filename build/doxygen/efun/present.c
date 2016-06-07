public class efun {
   /**
    * This efun checks if an object is present in a given environment.
    * The object is identified by id <str> or by an object <ob>. This
    * latter form of the efun can be used as a fast way to test for the
    * presence of a known object.
    * 
    * When searching objects by id, the efun by default returns the first
    * object found matching the id. In order to search for other than the
    * first object, a number can be specified either directly as the
    * argument <n>, or implicetely inside the <str> in the form "<id>
    * <n>".
    * 
    * By default, the efun searches first in the inventory of
    * this_object(), then in its environment. However, if <env> is given,
    * the efun searches just inside <env>.
    * 
    * When searching both inventory and environment of this_object(),
    * the numbering is applied linear over both spaces (see examples).
    * 
    * The driver identifies objects by calling the lfun id() in each
    * object.
    * 
    * @synopsis{
    * object present(string str)
    * object present(string str, int n)
    * object present(string str, object env)
    * object present(string str, int n, object env)
    * object present(object ob)
    * object present(object ob, object env)
    * }
    * 
    * @usage{
    * present("chest");
    * 
    * --> returns the first 'chest' object in this object.
    * 
    * present("chest 2")
    * 
    * --> returns the second 'chest' object in this object.
    * 
    * present("chest 2", 1)
    * 
    * --> returns the first 'chest 2' object in this object.
    * Assume there is one "chest" inside the current object, and
    * two in its environment:
    * present("chest", 1) -> returns the chest inside
    * present("chest", 2) -> returns the first chest outside
    * present("chest", 3) -> returns the second chest outside
    * A typical 2.4.5-implementation of the "do <id> <n>" command style
    * is:
    * void init() { add_action("open_chest", "open"); }
    * 
    * int open_chest (string str) {
    * 
    * if (present (str) != this_object ())
    * 
    * return 0; /* Not this chest */
    * 
    * ...
    * 
    * }
    * }
    * 
   **/
   object present(object ob, object env);
}
