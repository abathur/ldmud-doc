public class efun {
   /**
    * @synopsis{
    * string object_name()
    * }
    * 
   **/
   string object_name();
}
string object_name(object ob)

Get the name of an object <ob> or, if no argument is given, of
the current object.

As a special case, if <ob> is 0, the function returns 0.

This name is the name under which the object is stored in the
muds object table. It is initialised at the creation of the
object such that blueprints are named after the file they are
compiled from (without the trailing '.c'), and clones receive
the name of their blueprint, extended by '#' followed by
a unique non-negative number. These rules also apply to
virtual objects - the real name/type of virtual objects
is ignored.

The name of an object can be changed with rename_object(), and
object_name() will reflect any of these changes.

The returned name always begins with '/' (absolute path),
except when the parser runs in COMPAT mode.

EXAMPLES
   find_object(object_name(ob)) == ob

This is guaranteed to be true for all objects ob that are not
destructed.

0 is accepted as argument since 3.2.9.

      See Also: 
         efun::clone_object(), efun::load_name(), efun::load_object(), efun::find_object(),

   efun::object_time(), efun::program_name(), efun::rename_object()
