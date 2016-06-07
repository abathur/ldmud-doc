public class efun {
   /**
    * @synopsis{
    * int clonep()
    * int clonep(object obj)
    * int clonep(string obj)
    * int clonep(mixed  arg)
    * }
    * 
   **/
   int clonep(mixed  arg);
}
The efun returns 1 if <obj> is a clone, and 0 if it is not.
The <obj> can be given as the object itself, or by its name.
If <obj> is omitted, the current object is tested.
Arguments of other types return 0.
Objects with replaced programs no longer count as clones.

EXAMPLES
object o;
o = clone_object("/std/thing");
write(clonep(o));                           --> writes "1"
write(clonep("/std/thing"))                 --> writes "0"

(In COMPAT_MODE use "std/thing" as the filename)

Introduced in LDMud 3.2.6, changed in 3.2.7 so that objects
with replaced programs no longer count as clones.

      See Also: 
         efun::load_name(), efun::clone_object(), efun::clones(), efun::closurep(), efun::floatp(),

   efun::mappingp(), efun::objectp(), efun::intp(), efun::referencep(), efun::pointerp(),
   efun::stringp(), efun::symbolp(), efun::structp()