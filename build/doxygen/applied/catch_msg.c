public class applied {
   /**
    * When efun::say(), efun::tell_room() or efun::tell_object() are used with a non-string as message, the value will be passed to applied::catch_msg() in all living objects that can hear it, instead of writing to the user resp. sending to applied::catch_tell(). This can be used to implement communication protocols between livings. The second argument denotes the object that has sent the message.
    * 
    * @synopsis{
    * void catch_msg(mixed *|struct|mapping|object msg, object obj)
    * }
    * 
    * @history{
    * changed (3.2.11) -- added tell_object() to the efuns calling this lfun for symmetry reasons.
    * changed (3.3.686) -- added the use of a mapping/struct/object as message value.
    * }
    * 
    * @see efun::say(), efun::tell_room(), applied::catch_tell()
   **/
   void catch_msg(mixed *|struct|mapping|object msg, object obj);
}
