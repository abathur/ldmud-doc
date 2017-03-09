public class efun {
   /**
    * Find an object with the object_name str. If the object isn't loaded, it will not be found.
    * 
    * @synopsis{
    * object find_object(string str)
    * }
    * 
    * @usage{
    * All four of these statements are equal:
    * 
    * ~~~{.c}
    * object obj;
    * obj = find_object("std/thing");
    * obj = find_object("std/thing.c");
    * obj = find_object("/std/thing");
    * obj = find_object("/std/thing.c");
    * 
    * ~~~
    * This one, however, returns the clone whose object_name is "std/thing#42", if it exists:
    * 
    * ~~~{.c}
    * obj = find_object("/std/thing#42");
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::object_name(), efun::to_object()
   **/
   object find_object(string str);
}
