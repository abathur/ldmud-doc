public class efun {
   /**
    * @synopsis{
    * void write(mixed msg)
    * }
    * 
   **/
   void write(mixed msg);
}
DESCRIPTION
Write out something to the current user. What exactly will
be printed in the end depends of the type of msg.

If it is a string or a number then just prints it out.

If it is an object then the object will be printed in the
form: "OBJ("+object_name((object)mix)+")"

If it is an array just "<ARRAY>" will be printed.
If it is a mapping just "<MAPPING>" will be printed.
If it is a closure just "<CLOSURE>" will be printed.

If the write() function is invoked by a command of a living,
non-interactive object and the given argument is a string
then the lfun catch_tell() of the living will be invoked with
the message as argument.

EXAMPLES
write("Hello world!n");

Just print out a string.

write(this_player());

This will print out something like "OBJ(std/player#1234)".

write( ({ "blub" }) );

Will print out "<ARRAY>".

   See Also: 
      efun::say(), efun::tell_object(), efun::tell_room(), applied::catch_tell()