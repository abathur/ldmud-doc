.. efun:: void say(string str)
  void say(string str, object exclude)
  void say(string str, object *excludes)
  void say(mixed *|mapping|struct|object msg)
  void say(mixed *|mapping|struct|object msg, object exclude)
  void say(mixed *|mapping|struct|object msg, object *excludes)

  There are two major modes of calling:

  If the first argument is a string :arg:`str`, it will be send to all livings in the current room except to the initiator.

  If the first argument is an array/mapping/struct/object :arg:`msg`, lfun :applied:`catch_msg` of all living objects except the initiator will be called. This :arg:`msg` will be given as first argument to the lfun, and the initiating object as the second.

  .. warning:: If the lfun :applied:`catch_msg` modifies the content of :arg:`msg`, all subsequent objects will receive the modified :arg:`msg`.

  By specifying a second argument to the efun one can exclude more objects than just the initiator. If the second argument is a single object :arg:`exclude`, both the given object and the initiator are excluded from the call. If the second argument is an array :arg:`excludes`, all objects and just the objects in this array are excluded from the call.

  The 'initiator' is determined according to these rules:

  - if the :efun:`say` is called from within a living object, this becomes the initiator
  - if the :efun:`say` is called from within a dead object as result of a user action (i.e. ``this_player()`` is valid), ``this_player()`` becomes the initiator.
  - Else the object calling the :efun:`say` becomes the initiator.

  .. usage::

    Both of these calls are equal when called by a non-living object::

      say("Hi!\n");
      say("Hi!\n", this_player());

    The next example shows how :efun:`say` works with :applied:`catch_tell`. The 2nd object must not be living so the :efun:`write` will go to the current user.

    Object 1 (living)::

      void catch_tell(string str) {
        write("Received: "+str+"\n");
      }

    Object 2 (not living)::

      void func() {
        ...
        say("HiHo!\n");
        ...
      }

    This more complex example demonstrates how :efun:`say` and :applied:`catch_msg` work. Here we also use a non living object to send the message so the who in :applied:`catch_msg` will be the current user.

    Object 1 (living)::

      void catch_msg(mixed *arr, object who) {
        int i;
        if(!arr) return;
        for(i=0; i<sizeof(arr); i++)
          tell_object(who, (stringp(arr[i]) ? arr[i] : "-/-")+"\n");
      }

    Object 2 (not living)::

      void func() {
        ...
        say( ({ "Hello", "there!" }) );
        ...
      }

  :history 3.3.686 changed: added the use of a mapping/struct/object as second argument.

  .. seealso:: :efun:`write`, :efun:`tell_object`, :efun:`tell_room`
