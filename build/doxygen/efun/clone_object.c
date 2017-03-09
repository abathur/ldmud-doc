public class efun {
   /**
    * Clone a new object from definition \p name, or alternatively from the object \p template. In both cases, the new object is given an unique name and returned.
    * 
    * The original used for cloning, called blueprint, should not be used in the system, just for cloning. The cloned objects contain only the data but the blueprint also the function code. The blueprint is the one without a unique number at the end of the object's name. The efun::clone_object() function never returns a blueprint.
    * 
    * If the \p name or \p template designates a cloned object itself, the system looks up the blueprint object _by >>name_<<.
    * 
    * If the blueprint exists and has a applied::heart_beat(), efun::clone_object() turns it off.
    * 
    * Note that the pathname must be complete, which means there are no relative paths allowed.
    * 
    * If strict euids are enforced, the cloning object must have a non-zero euid.
    * 
    * ## Variable Initialization #
    * 
    * In general, variables are initialized for blueprints and clones alike with a call to the internal lfun `__INIT()`.
    * 
    * However, if @ref driver_syntax_pragma "share_variables" is in effect (either explicitely given in the source or implicitely as runtime option), the values for a clone's uninitialized variables are taken from the _current_ variables of the object's blueprint.
    * 
    * In the absence of share_variables, variables without explicit initializers are initialized to 0.
    * 
    * Clone a torch (filename in non-compat format):
    * 
    * ~~~{.c}
    * object torch;
    * torch = clone_object("/obj/torch");
    * 
    * ~~~
    * Clone two keys (filename in compat format):
    * 
    * ~~~{.c}
    * object key1, key2;
    * key1 = clone_object(load_object("obj/key"));
    * key2 = clone_object(key1);
    * 
    * ~~~
    * Create a specialized weapons blueprint:
    * 
    * ~~~{.c}
    * --- std/weapon.c: ---
    * #pragma share_variables
    * int weapon_class = 1;
    * 
    * --- broadsword.c: ---
    * inherit "/std/weapon";
    * 
    * int create() {
    *     weapon_class = 2;
    *     replace_program("/std/weapon");
    * }
    * 
    * ~~~
    * 
    * @synopsis{
    * object clone_object(string name)
    * object clone_object(object template)
    * }
    * 
    * @usage{
    * }
    * 
    * @history{
    * changed (3.2.6) -- takes an object as argument.
    * changed (3.3.378) -- consolidates variable initialization with share_variables.
    * }
    * 
    * @see efun::blueprint(), efun::clonep(), efun::destruct(), efun::clones(), efun::load_name(), efun::load_object(), efun::move_object(), efun::program_name(), @ref driver_syntax_pragma "pragma"
   **/
   object clone_object(object template);
}
