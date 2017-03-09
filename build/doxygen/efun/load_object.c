public class efun {
   /**
    * Load the object from the file \p name (which can not be empty) and return it. If the object already exists, just return it.
    * 
    * This efun can be used only to load blueprints; for clones, use efun::clone_object().
    * 
    * If strict euids are enforced, the cloning object must have a non-zero euid.
    * 
    * @synopsis{
    * object load_object(string name)
    * }
    * 
    * @usage{
    * Update and reload the standard player object:
    * 
    * ~~~{.c}
    * destruct(find_object("/std/player"));
    * load_object("/std/player");
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * changed (3.3.716) -- requires that name is not empty.
    * }
    * 
    * @see efun::clone_object()
   **/
   object load_object(string name);
}
