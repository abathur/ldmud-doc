.. efun:: string * include_list()
  string * include_list(object ob)
  string * include_list(object ob, int flags)
  :include: <include_list.h>

  Return information about all files included into the compilation of :arg:`ob`, including :arg:`ob` program's own filename. If :arg:`ob` is omitted, it defaults to the current object.

  In the resulting array(s), the information for one include file takes up three elements:

    string [i+0]: the name as it appeared in the program, including the delimiters ("" or <>, resp.).
    string [i+1]: the absolute filename of the include file.
    int    [i+2]: the inclusion depth (usually 1, more for nested includes).

  The first entry in the result is the program's own name in [i+0], the other two elements [i+1] and [i+2] are 0.

  The :arg:`flags` determines the exact structure of the result:

  :arg:`flags` = :macro:`INCLIST_FLAT` (0, default):
    The result is a flat array of the entries, starting the with the entry for :arg:`ob` itself, followed by the entries for all included files in the order they were encountered.

  :arg:`flags` = :macro:`INCLIST_TREE` (1):
    The result is an array starting the with the entry of :arg:`ob` itself, followed by the entries for all directly included files. If one of the included files has no nested includes by itself, then its information will be stored directly in the array. If one included file has includes by itself, a subvector will be created and stored in the result vector (again in [i+0], with [i+1] and [i+2] being 0). These subvectors have the same structure as the main result vector.

  If objects, including :arg:`ob`, had been undergone a :efun:`replace_program`, the returned filenames will reflect the actual active program.

  The returned proper include filenames always begin with '/' (absolute path), even when the parser runs in :macro:`__COMPAT_MODE__` mode. The filename of the object itself however does not begin with a '/' in :macro:`__COMPAT_MODE__` mode.

  .. usage::

    Given this source code (and /sys as system include directory):

    .. code-block::
      :caption: a.c

      #include "b.h"
      #include <c.h>

    .. code-block::
      :caption: b.h

      #include "d.h"

    .. code-block::
      :caption: c.h

      #define BAR

    .. code-block::
      :caption: d.h

      #define FOO

    the efun will give these results::

      include_list(a, INCLIST_FLAT)
      /* returns:
        ({ "a.c", 0, 0
          , "\"b.h\"", "/.../b.h", 1
          , "\"d.h\"", "/.../d.h", 2
          , "<c.h>",   "/sys/c.h", 1
        })
      */

      include_list(a, INCLIST_TREE)
      /* returns:
        ({ "a.c", 0, 0
        , ({ "\"b.h\"", "/.../b.h", 1
           , "\"d.h\"", "/.../d.h", 2
          }), 0, 0
        , "<c.h>",   "/sys/c.h", 1
        })
      */

  :history 3.2.9/3.3.128 introduced:

  .. seealso:: :efun:`debug_info`, :efun:`inherit_list`
