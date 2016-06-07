public class efun {
   /**
    * @synopsis{
    * object load_object(string name)
    * }
    * 
   **/
   object load_object(string name);
}
Load the object from the file <name> (which can not be empty) and
return it. If the object already exists, just return it.

This efun can be used only to load blueprints - for clones, use
the efun clone_object().

If strict euids are enforced, the cloning object must have
a non-zero euid.

EXAMPLES
// Update and reload the standard player object
destruct(find_object("/std/player"));
load_object("/std/player");

Introduced in LDMud 3.2.6.
LDMud 3.3.716/3.4.3 requires that the <name> is not empty.

   See Also: 
      efun::clone_object()
