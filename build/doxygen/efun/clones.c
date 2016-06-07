public class efun {
   /**
    * @synopsis{
    * object * clones()
    * object * clones(int what)
    * object * clones(string|object obj [, int what])
    * }
    * 
   **/
   object * clones(string|object obj [, int what]);
}
The efuns returns an array with all clones of a certain blueprint.
The array is subject to the usual runtime limits.

If <obj> is given, all clones of the blueprint of <obj> (which
may be <obj> itself) are returned, otherwise all clones of the
current object resp. of the current object's blueprint. If <obj>
is given as string, it must name an existing object.

<what> selects how to treat clones made from earlier versions
of the blueprint:

   == 0: (default) return the clones of the current blueprint only.
   == 1: return the clones of the previous blueprints only.
   == 2: return all clones of the blueprint.

Note: this efun is computationally expensive.

If the driver is compiled with DYNAMIC_COSTS, the cost of this
efun is proportional to the number of objects in the game.

EXAMPLES
object o, p;
o = clone_object("/std/thing"); /* or "std/thing" in COMPAT mode >>*<</
destruct(find_object("/std/thing"));
p = clone_object("/std/thing");

clones("/std/thing")    --> returns ({ p })
clones("/std/thing", 0) --> returns ({ p })
clones("/std/thing", 1) --> returns ({ o })
clones("/std/thing", 2) --> returns ({ o, p })

Introduced in LDMud 3.2.8.
LDMud 3.2.9 added the dynamic cost.

   See Also: 
      efun::blueprint(), efun::clone_object(), efun::clonep()
