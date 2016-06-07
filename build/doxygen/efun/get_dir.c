public class efun {
   /**
    * @synopsis{
    * mixed * get_dir(string str)
    * mixed * get_dir(string str, int mask)
    * :include <files.h>()
    * }
    * 
   **/
   :include <files.h>();
}
This function takes a path as argument and returns an array of file
names and attributes in that directory.

Returns 0 if the directory to search in does not exist.

The filename part of the path may contain '*' or '?' as wildcards:
every '*' matches an arbitrary amount of characters (or just itself),
a '?' matches any character. Thus get_dir("/path/<em>") would return an
alphabetically sorted array of all files in directory "/path", or
just ({ "/path/</em>" }) if this file happens to exist.

To query the content of a directory, use the directory name with a
trailing '/' or '/.', for example get_dir("/path/."). Use the
directory name as it is to get information about the directory itself.

The optional second argument mask can be used to get
information about the specified files.

GETDIR_EMPTY    (0x00)  get_dir returns an empty array (not very
   useful).

GETDIR_NAMES    (0x01)  put the alphabetically sorted file names into
   the returned array.

GETDIR_SIZES    (0x02)  put the file sizes unsorted into the returned
   array. directories have size FSIZE_DIR (-2).

GETDIR_DATES    (0x04)  put the file modification dates (in seconds
   since 01/01/1970) unsorted into the
   returned array.

GETDIR_ACCESS   (0x40)  put the file access dates unsorted into
   the returned array.

GETDIR_MODES    (0x80)  put the unix file modes unsorted into
   the returned array.

GETDIR_ALL      (0xDF)  Return all.

GETDIR_PATH     (0x10)  if this mask bit is set, the filenames with
   the full path will be returned
   (GETDIR_NAMES is implied).

GETDIR_UNSORTED (0x20)  if this mask bit is set, the result of will
   _not_ be sorted.

Note: You should use GETDIR_NAMES|GETDIR_UNSORTED to get the entries
in the same order as with GETDIR_SIZES and GETDIR_DATES.

The values of mask can be added together.

NOTES
The path argument to this efun is processed by valid_read() in the
mudlib master before being used. The mudlib may normalize this path
(e.g. strip leading or trailing "/") and this may lead to expected
results (e.g. get_dir("/dir/", ...) not returning the contents
of /dir/).
COMPAT mode: GETDIR_PATH will return the paths without leading /.

EXAMPLES
function                         returns
-------------------------------------------------------------------
get_dir("/obj/.")                all files contained in directory /obj.
get_dir("/obj/")                 the same as get_dir("/obj/")

get_dir("/obj/sword.c")          ({ "sword.c" }) if /obj/sword.c
   exists (it may be a file or a
   directory), otherwise ({ }) if
   /obj is a directory,
   otherwise 0.

get_dir("/obj/<em>")                ({ "</em>" }) if * exists.
   otherwise and normally an
   alphabetically sorted array with all
   names of files and directories in
   /obj if /obj is a directory,
   otherwise 0.

get_dir("/obj/sword.c", GETDIR_SIZES)  ({ <size of /obj/sword.c> })
   if that file exists.

get_dir("/obj/.", GETDIR_NAMES)  the same as get_dir("/obj/.").
get_dir("/obj/.", GETDIR_SIZES)  an array with the sizes of the files

   in /obj, not sorted by names.

get_dir("/obj/.", GETDIR_NAMES|GETDIR_SIZES|GETDIR_DATES) or shorter
get_dir("/obj/.", GETDIR_ALL)    an one-dimensional array that

   contains for each file in /obj its
   name, its size and its modification
   date, sorted by names, for example

      ({
         "axe.c"  ,  927, 994539583,
         "sword.c", 1283, 998153903,

      }).

get_dir("/obj/sword.c", GETDIR_NAMES|GETDIR_PATH)
   ({ "/obj/sword.c" }) if applicable.

get_dir("/obj/sword.c", GETDIR_PATH)  Short form of the same query.

transpose_array(({ get_dir(str, GETDIR_NAMES|GETDIR_UNSORTED)
   , get_dir(str, GETDIR_SIZES)
   , get_dir(str, GETDIR_DATES) }));

This returns an array of arrays, with filename, size and
filetime as elements, not sorted by names, for example

   ({
      ({ "sword.c", 1283, 998153903 }),
      ({ "axe.c"  ,  927, 994539583 }),

   }).

LDMud 3.2.9 added GETDIR_PATH.
LDMud 3.2.11/3.3.648 added GETDIR_ACCESS and GETDIR_MODES.

      See Also: 
         efun::mkdir(), efun::rmdir(), efun::file_size(), efun::write_file(), efun::write_bytes(),

   efun::read_file(), efun::read_bytes()
