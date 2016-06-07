public class applied {
   /**
    * When a message is sent to an non-interactive object, via @asay()`, @atell_object()`, @atell_room()` or @awrite()`, it will get to the function @acatch_tell(string)`. The idea is to enable communications between NPCs and from a user to an NPC.
    * 
    * Messages sent to an interactive object are also passed to that object's @acatch_tell()` lfun, <em>if it has one</em>. If the receiver (or one of its shadows) doesn't have that lfun, the text is sent to the socket directly. Only messages sent by an interactive object to itself inside a catch_tell are always written to the socket immediately.
    * 
    * This allows text to be filtered and processed before it is written to a player.
    * 
    * @synopsis{
    * void catch_tell(string)
    * }
    * 
    * @see efun::enable_commands(), efun::say(), efun::tell_object(), efun::tell_room(), efun::write(), efun::snoop(), applied::catch_msg()
   **/
   void catch_tell(string);
}
