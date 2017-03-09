public class efun {
   /**
    * Starts a snoop from \p snooper on \p snoopee, or if \p snoopee is not given, terminates any snoop from \p snooper.
    * 
    * Return \p snoopee on success, or 0 for a failure (including snooping loops).
    * 
    * The snoop is checked with the master object for validity. It will also fail if a snoop would result in a recursive snoop action.
    * 
    * \p snooper can be an interactive player or an object. If it is an interactive player, the snooped text is prepended with a '%' and sent directly to the player's connection. If \p snooper is an object, the snooped text is sent in two calls to the object's applied::catch_tell() lfun: the first call passes just the "%" (plus the prompt if the object changed it), the second the actual text.
    * 
    * @synopsis{
    * object snoop(object snooper)
    * object snoop(object snooper, object snoopee)
    * }
    * 
    * @see efun::query_snoop(), applied::catch_tell()
   **/
   object snoop(object snooper, object snoopee);
}
