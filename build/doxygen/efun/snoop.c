public class efun {
   /**
    * @synopsis{
    * object snoop(object snooper)
    * object snoop(object snooper, object snoopee)
    * }
    * 
   **/
   object snoop(object snooper, object snoopee);
}
Starts a snoop from 'snooper' on 'snoopee', or if 'snoopee' is not
given, terminates any snoop from 'snooper'.

Return <snoopee> on success, or 0 for a failure (including snooping
loops).

The snoop is checked with the master object for validity.  It
will also fail if a snoop would result in a recursive snoop
action.

<snooper> can be an interactive player or an object. If it is
an interactive player, the snooped text is prepended with a
'%' and sent directly to the player's connection. If <snooper>
is an object, the snooped text is sent in two calls to the
object's catch_tell() lfun: the first call passes just the
"%" (plus the prompt if the object changed it), the second the
actual text.

   See Also: 
      efun::query_snoop(), applied::catch_tell()
