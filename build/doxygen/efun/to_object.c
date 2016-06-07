public class efun {
   /**
    * @synopsis{
    * object to_object(string arg)
    * object to_object(closure arg)
    * object to_object(object arg)
    * (object)<value>()
    * }
    * 
   **/
   (object)<value>();
}
DESCRIPTION
The argument is converted into an object, if possible.

For strings, the object with a matching object_name() is
returned, or 0 if there is none, as find_object() does.

For (bound!) closures, the object holding the closure is
returned (for 'alien lfun closures' this is the object which
created the closure, not the object the lfun is defined in).

Objects and the number 0 return themselves.

BUGS
The cast notation only works if the precise type of <value>
is known at compile-time. This will not be fixed - use the
function form instead.

      See Also: 
         efun::find_object(), efun::to_array(), efun::to_int(), efun::to_string(),

   efun::get_type_info()
