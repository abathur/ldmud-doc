public class efun {
   /**
    * Write out something to the current user. What exactly will be printed in the end depends of the type of \p msg:
    * 
    * - If it is a string or a number then just prints it out.
    * - If it is an object then the object will be printed in the form: `"OBJ("+object_name((object)mix)+")"`
    * - If it is an array just `<ARRAY>` will be printed.
    * - If it is a mapping just `<MAPPING>` will be printed.
    * - If it is a closure just `<CLOSURE>` will be printed.
    * 
    * If the function is invoked by a command of a non-interactive living object (such as an NPC) and the given argument is a string, the lfun applied::catch_tell() of the living will be invoked with the message as argument.
    * 
    * @synopsis{
    * void write(mixed msg)
    * }
    * 
    * @usage{
    * Just print out a string:
    * 
    * ~~~{.c}
    * write("Hello world!\n");
    * 
    * ~~~
    * Other types are mostly just useful for debug purposes:
    * 
    * ~~~{.c}
    * write(this_player());  // prints "OBJ(std/player#1234)"
    * write( ({ "blub" }) ); // prints "<ARRAY>"
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::say(), efun::tell_object(), efun::tell_room(), applied::catch_tell()
   **/
   void write(mixed msg);
}
