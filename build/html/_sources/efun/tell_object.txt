.. efun:: void tell_object(object|string ob, string str)
  void tell_object(object|string ob, mixed *|mapping|struct|object msg)

  Send a message <str> to object <ob> (which is looked up and loaded
  by given name if necessary).

  If the second argument is a string, the message will be printed
  to <ob> if it is an interactive user, otherwise it will be passed to
  the lfun catch_tell() on the target living object.

  If the second argument is an array/mapping/struct/object, it will be
  passed to the lfun catch_msg() on the target.

  .. usage::

    Just tell Wessex a simple "Hi!"::

      object who;
      who=find_player("wessex");
      tell_object(who, "Hi!\n");

  This examples shows how tell_object() works with catch_tell()::

    Object 1 (living with the name "dummymonster"):
       void catch_tell(string str) {
          write("Received: "+str+"\n");
       }
    Object 2:
       void func() {
          object who;
          who=find_living("dummymonster");
          tell_object(who, "Follow me, mortal one!\n");
          ...
       }

.. history
  LDMud 3.2.11 introduced the 'mixed *' form for symmetry reasons.
  LDMud 3.3.686 added the use of a mapping/struct/object as second
  argument.

  .. seealso:: :efun:`write`, :efun:`say`, :applied:`catch_tell`, :applied:`catch_msg`
