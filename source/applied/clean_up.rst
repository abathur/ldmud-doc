.. applied:: int clean_up(int refcount)
  int <closure>(int ref, object ob)

  .. todo:: this may need to have the closure form above rmed (some others in directory have a similar issue); the problem is on the one hand that the applied directory isn't equipped to handle them well, and on the other they are technically documenting the hook/closure forms and not strictly the apply, making everything really murky. Perhaps this is a structural problem because the applied concept is a relic, but the documentation attempts to bridge between the old/obsolete concept and the new versions of the same in hook. In this case, the "answer" might just be that applied needs to be removed, moved to obsolete, trimmed down to a single readme pointing to hooks, or trimmed down to a bunch of stubs pointing to the proper hook for handling the same behavior. Note: angled brackets around closure above break the function signature parse...

  :hook:`H_CLEAN_UP` defines a lfun or a closure used to clean up an object. In older drivers this was hardwired to the lfun :applied:`clean_up`.

  The function is applied by the driver when an object hasn't been used for a long time, to give it a chance to self-destruct. The refcount :arg:`ref` passed as argument will be 0 for clone objects, 1 for a simple loaded object, and greater when the object is cloned or inherited by some existing object. It is recommended not to self_destruct the object when the reference count is greater than one.

  By convention, a refcount < 0 is used if some other object asks the called object to clean_up.

  If the function is a closure, the second argument :arg:`ob` is the object to clean up.

  If the hook specifies a non-existing lfun, or if the call returns 0, no further attempt to clean up this object will be made.

  Returning a non-zero value is only recommended when the reason why the object can't self-destruct is likely to vanish without the object being touched, that is, when no local function is called in it, (and in compat mode also when the object is not being moved around).

  A typical mud configuration defines the time to wait for ``clean_up()`` so long that you can assert ``reset()`` has been called since the object has been touched last time.

  .. todo:: below probably needs actual code, if the document stays and the hook isn't already well-documented.

  .. usage::

    A clone of ``/std/drink`` defines ``clean_up()`` to self-destruct if it is empty, not carried a living being and not touched for a long time.

    A room that inherits ``/std/room`` defines ``clean_up()`` to self-destruct if it is neither inherited nor used as a blueprint, is empty and was not entered for a long time.

  :history 3.2.1 changed: function no longer hardwired to the lfun :applied:`clean_up`.

  .. seealso:: :applied:`reset`, :applied:`heart_beat`, :efun:`call_out`, :efun:`destruct`, :applied:`remove`, :overview:`hook`
