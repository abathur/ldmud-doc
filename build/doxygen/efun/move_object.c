public class efun {
   /**
    * @synopsis{
    * void move_object(mixed item, mixed dest)
    * }
    * 
   **/
   void move_object(mixed item, mixed dest);
}
The item, which can be an object_name or an object, is moved into
it's new environment dest, which can also be an object_name or an
object.

Since 3.2.1, the innards of move_object() are implemented in
the mudlib, using the M_MOVE_OBJECT0/1 driver hooks, and move_object()
might as well be an simul-efun.

The traditional implementation restricted for !compat mode
the <item> to the calling object only.

   See Also: 
      applied::remove(), applied::init(), efun::transfer(), @ref driver_concepts_native "native", `hooks`, efun::set_environment()
