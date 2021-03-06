.. efun:: string * inherit_list()
  string * inherit_list(object ob)
  string * inherit_list(object ob, int flag)
  :include: <inherit_list.h>

  Returns the names of all files inherited by :arg:`ob`, including :arg:`ob's <ob>` own filename. If :arg:`ob` is omitted, it defaults to the current object. The value of :arg:`flag` determines the structure of the output.

  :arg:`flag` = :macro:`INHLIST_FLAT` (0, default):
    The result is an array of filenames, starting the with the filename of :arg:`ob` itself, followed by the names of all inherited objects in breadth order.

  :arg:`flag` = :macro:`INHLIST_TREE` (1):
    The result is an array starting the with the filename of :arg:`ob` itself, followed by the all directly inherited objects. If one of the inherited objects has no inherits by itself, then its name will be stored directly in the array. If one inherited object has inherits by itself, a subvector will be created and stored in the result vector. The subvector(s) have the same structure as the main result vector.

  :arg:`flag` = :macro:`INHLIST_TAG_VIRTUAL` (2):
    All names in the result are prefixed with a tag: "  " (two spaces) for normal inherits, "v " for virtual inherits.

  All flags can be combined with binary "or" (``|``), though :macro:`INHLIST_FLAT` and :macro:`INHLIST_TREE` are mutually exclusive.

  If objects, including :arg:`ob`, had been undergone a :efun:`replace_program`, the returned filenames will reflect the actual active program.

  The returned names always begin with '/' (absolute path), except when the parser runs in :macro:`__COMPAT_MODE__`.

  .. usage::

    Given this inheritance structure:

    - a

      - c

        - d

      - b

    the efun will give the following results::

      inherit_list(a)     // ({ "a", "c", "b", "d" })
      inherit_list(c)     // ({ "c", "d" })
      inherit_list(a, 1)  // ({ "a", ({ "c", "d" }), "b" })

  :history 3.2.8 changed: the returned names now start with a '/'.
  :history 3.2.9/3.3.111 changed: added the tree representation.
  :history 3.2.9/3.3.125 changed: added the tagging of virtual inherits.

  .. seealso:: :efun:`debug_info`, :efun:`include_list`
