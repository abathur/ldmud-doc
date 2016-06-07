public class efun {
   /**
    * Returns the names of all files inherited by <ob>, including
    * <ob>s own filename. If <ob> is omitted, it defaults to the current
    * object. The value of <flags> determines the structure of the output.
    * 
    * <flag> = INHLIST_FLAT (0, default):
    * The result is an array of filenames, starting the with the filename
    * of <ob> itself, followed by the names of all inherited objects
    * in breadth order.
    * 
    * <flag> = INHLIST_TREE (1):
    * The result is an array starting the with the filename
    * of <ob> itself, followed by the all directly inherited
    * objects. If one of the inherited objects has no inherits by itself,
    * then its name will be stored directly in the array. If one inherited
    * object has inherits by itself, a subvector will be created and
    * stored in the result vector. The subvector(s) have the same
    * structure as the main result vector.
    * 
    * <flag> = INHLIST_TAG_VIRTUAL (2):
    * All names in the result are prefixed with a tag: "  " (two spaces)
    * for normal inherits, "v " for virtual inherits.
    * 
    * All flags can be combined with binary->>|<<, just _FLAT and _TREE are
    * mutually exclusive.
    * 
    * If objects, including <ob>, had been undergone a replace_program(),
    * the returned filenames will reflect the actual active program.
    * 
    * The returned names always begin with '/' (absolute path), except
    * when the parser runs in COMPAT mode.
    * 
    * @headerfile <inherit_list.h>
    * 
    * @synopsis{
    * string * inherit_list()
    * string * inherit_list(object ob)
    * string * inherit_list(object ob, int flags)
    * }
    * 
    * @usage{
    * Given this inheritance structure:
    * / c - d
    * 
    * a
    * 
    * b
    * the efun will give the following results:
    * inherit_list(a) -> ({ "a", "c", "b", "d" })
    * inherit_list(c) -> ({ "c", "d" })
    * inherit_list(a, 1) -> ({ "a", ({ "c", "d" }), "b" })
    * }
    * 
   **/
   string * inherit_list(object ob, int flags);
}