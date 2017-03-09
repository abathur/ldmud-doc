public class efun {
   /**
    * Send a message \p str to object \p ob (which is looked up and loaded by given name if necessary).
    * 
    * If the second argument is a string, the message will be printed to \p ob if it is an interactive user, otherwise it will be passed to the lfun applied::catch_tell() on the target living object.
    * 
    * If the second argument is an array/mapping/struct/object, it will be passed to the lfun applied::catch_msg() on the target.
    * 
    * @synopsis{
    * void tell_object(object|string ob, string str)
    * void tell_object(object|string ob, mixed *|mapping|struct|object msg)
    * }
    * 
    * @usage{
    * Just tell Wessex a simple "Hi!":
    * 
    * ~~~{.c}
    * object who;
    * who = find_player("wessex");
    * tell_object(who, "Hi!\n");
    * 
    * ~~~
    * This examples shows how efun::tell_room() works with applied::catch_tell():
    * 
    * Object 1 (living with the name "dummymonster"):
    * 
    * ~~~{.c}
    * void catch_tell(string str) {
    *   write("Received: "+str+"\n");
    * }
    * 
    * ~~~
    * Object 2:
    * 
    * ~~~{.c}
    * void func() {
    *   object who;
    *   who=find_living("dummymonster");
    *   tell_object(who, "Follow me, mortal one!\n");
    *   ...
    * }
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * changed (3.2.11) -- added the 'mixed *' form for symmetry reasons.
    * changed (3.3.686) -- added the use of a mapping/struct/object as second argument.
    * }
    * 
    * @see efun::write(), efun::say(), applied::catch_tell(), applied::catch_msg()
   **/
   void tell_object(object|string ob, mixed *|mapping|struct|object msg);
}
