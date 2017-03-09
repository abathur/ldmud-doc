public class efun {
   /**
    * Returns the names of all files inherited by \p ob, including \p ob own filename. If \p ob is omitted, it defaults to the current object. The value of \p flag determines the structure of the output.
    * 
    * \p flag = `INHLIST_FLAT` (0, default):
    * The result is an array of filenames, starting the with the filename of \p ob itself, followed by the names of all inherited objects in breadth order.
    * 
    * \p flag = `INHLIST_TREE` (1):
    * The result is an array starting the with the filename of \p ob itself, followed by the all directly inherited objects. If one of the inherited objects has no inherits by itself, then its name will be stored directly in the array. If one inherited object has inherits by itself, a subvector will be created and stored in the result vector. The subvector(s) have the same structure as the main result vector.
    * 
    * \p flag = `INHLIST_TAG_VIRTUAL` (2):
    * All names in the result are prefixed with a tag: "  " (two spaces) for normal inherits, "v " for virtual inherits.
    * 
    * All flags can be combined with binary "or" (`|`), though `INHLIST_FLAT` and `INHLIST_TREE` are mutually exclusive.
    * 
    * If objects, including \p ob, had been undergone a efun::replace_program(), the returned filenames will reflect the actual active program.
    * 
    * The returned names always begin with '/' (absolute path), except when the parser runs in @ref driver_topics_predefined "__COMPAT_MODE__".
    * 
    * @headerfile <inherit_list.h>
    * 
    * @synopsis{
    * string * inherit_list()
    * string * inherit_list(object ob)
    * string * inherit_list(object ob, int flag)
    * }
    * 
    * @usage{
    * Given this inheritance structure:
    * 
    * - a
    * - c
    *  - d
    * - b
    * 
    * the efun will give the following results:
    * 
    * ~~~{.c}
    * inherit_list(a)     // ({ "a", "c", "b", "d" })
    * inherit_list(c)     // ({ "c", "d" })
    * inherit_list(a, 1)  // ({ "a", ({ "c", "d" }), "b" })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.8) -- the returned names now start with a '/'.
    * changed (3.2.9/3.3.111) -- added the tree representation.
    * changed (3.2.9/3.3.125) -- added the tagging of virtual inherits.
    * }
    * 
    * @see efun::debug_info(), efun::include_list()
   **/
   string * inherit_list(object ob, int flag);
}
