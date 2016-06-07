public class efun {
   /**
    * @synopsis{
    * object blueprint()
    * object blueprint(string|object ob)
    * }
    * 
   **/
   object blueprint(string|object ob);
}
The efuns returns the blueprint for the given object <ob>, or for
the current object if <ob> is not specified.

If the blueprint is destructed, or its program replaced, the efun
returns 0.

For objects with replaced programs, the efun returns the blueprint
for the replacement program.
In COMPAT mode the returned blueprint does not start with a "/".

EXAMPLES
blueprint("/std/thing"))               -> /std/thing
blueprint(find_object("/std/thing"))   -> /std/thing
blueprint(clone_object("/std/thing"))  -> /std/thing

Introduced in LDMud 3.2.9.

   See Also: 
      efun::clones(), efun::clone_object()
