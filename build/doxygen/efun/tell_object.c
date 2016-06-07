public class efun {
   /**
    * Send a message <str> to object <ob> (which is looked up and loaded
    * by given name if necessary).
    * 
    * If the second argument is a string, the message will be printed
    * to <ob> if it is an interactive user, otherwise it will be passed to
    * the lfun catch_tell() on the target living object.
    * 
    * If the second argument is an array/mapping/struct/object, it will be
    * passed to the lfun catch_msg() on the target.
    * 
    * This examples shows how tell_object() works with catch_tell():
    * 
    * ~~~{.c}
    * Object 1 (living with the name "dummymonster"):
    *    void catch_tell(string str) {
    *       write("Received: "+str+"\n");
    *    }
    * Object 2:
    *    void func() {
    *       object who;
    *       who=find_living("dummymonster");
    *       tell_object(who, "Follow me, mortal one!\n");
    *       ...
    *    }
    * 
    * ~~~
    * 
    * @synopsis{
    * void tell_object(object|string ob, string str)
    * void tell_object(object|string ob, mixed *|mapping|struct|object msg)
    * }
    * 
    * @usage{
    * Just tell Wessex a simple "Hi!":
    * object who;
    * who=find_player("wessex");
    * tell_object(who, "Hi!\n");
    * }
    * 
   **/
   void tell_object(object|string ob, mixed *|mapping|struct|object msg);
}
