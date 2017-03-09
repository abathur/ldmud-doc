public class efun {
   /**
    * The efuns returns the blueprint for the given object \p ob, or for the current object if \p ob is not specified.
    * 
    * If the blueprint is destructed, or its program replaced, the efun returns 0.
    * 
    * For objects with replaced programs, the efun returns the blueprint for the replacement program. In @ref driver_topics_predefined "__COMPAT_MODE__" the returned blueprint does not start with a "/".
    * 
    * @synopsis{
    * object blueprint()
    * object blueprint(string|object ob)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * blueprint("/std/thing"))               -> /std/thing
    * blueprint(find_object("/std/thing"))   -> /std/thing
    * blueprint(clone_object("/std/thing"))  -> /std/thing
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::clones(), efun::clone_object()
   **/
   object blueprint(string|object ob);
}
