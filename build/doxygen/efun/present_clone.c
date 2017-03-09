public class efun {
   /**
    * This efun searches the inventory of object \p env (default is `this_object()`) for an object with a specific blueprint. The blueprint can be specified either by name \p str, or as the same blueprint as of object \p obj. The matching criteria in both cases is the `load_name()`. If \p n is given, object \p n in \p env is returned (if present), otherwise the first object matching \p str or \p obj. If no object in \p env matches the criteria, 0 is returned.
    * 
    * @par note: In contrast to efun::present(), this efun never searches in the environment of \p env.
    * 
    * For plain driver this name starts with a '/', for @ref driver_topics_predefined "__COMPAT_MODE__" drivers it doesn't.
    * 
    * @synopsis{
    * object present_clone(string str)
    * object present_clone(string str, int n)
    * object present_clone(string str, object env)
    * object present_clone(string str, object env, int n)
    * object present_clone(object obj)
    * object present_clone(object obj, int n)
    * object present_clone(object obj, object env)
    * object present_clone(object obj, object env, int n)
    * }
    * 
    * @usage{
    * Assume that object \p env contains the objects `/obj/money#8`, `/std/weapon#9`, `/std/weapon#12` and `/obj/key` in the given order.
    * 
    * | Function call                                        | returns            |
    * |------------------------------------------------------|--------------------|
    * | `present_clone("/obj/money", env)`                   | `/obj/money#8`     |
    * | `present_clone("/std/weapon#12", env)`               | `/std/weapon#9`    |
    * | `present_clone(find_object("/obj/money#14"), env)`   | `/obj/money#8`     |
    * | `present_clone("/obj/key#18", env)`                  | `/obj/key`         |
    * | `present_clone("/std/weapon#12", env, 2)`            | `/std/weapon#12`   |
    * | `present_clone("/std/weapon#12", env, 3)`            | `0`                |
    * 
    * }
    * 
    * @history{
    * introduced (3.2.7)
    * changed (3.3.718) -- added searching for the :arg:`n`th object.
    * }
    * 
    * @see efun::load_name(), efun::present()
   **/
   object present_clone(object obj, object env, int n);
}
