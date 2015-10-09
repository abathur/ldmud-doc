.. efun:: void tell_room(string|object ob, string str)
  void tell_room(string|object ob, string str, object *exclude)
  void tell_room(string|object ob, mixed *|mapping|struct|object msg)
  void tell_room(string|object ob, mixed *|mapping|struct|object msg, object *exclude)

  Send a message <str> to all living objects in the room <ob>. <ob>
  can also be the name of the room given as a string. If a
  receiving object is not an interactive user, the lfun
  catch_tell() of the object will be invoked with the message as
  argument. If living objects define catch_tell(), the string
  will also be sent to that instead of being written to the user.
  If <ob> is given by filename, the driver looks up the object
  under that name, loading it if necessary. If array *<exclude> is
  given, all objects contained in *<exclude> are excluded from the
  message str.

  If the second arg is an array/mapping/struct/object, catch_msg() will
  be called in all listening living objects.

  .. usage::

  Just send a simple "Hi!" to all livings in the current::

    tell_object(environment(this_player()), "Hi!\n");

  This example shows how tell_room() works with catch_tell()::

    Object 1 (living):
       void catch_tell(string str) {
          write("Received: "+str+"\n");
       }
    Object 2:
       void func() {
          ...
          tell_room(environment(this_player()), "HiHo!\n");
          ...
       }

.. history
  LDMud 3.3.686 added the use of a mapping/struct/object as second
  argument.

  .. seealso:: :efun:`write`, :efun:`say`, :efun:`tell_object`, :applied:`catch_tell`, :applied:`catch_msg`
