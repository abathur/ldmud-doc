.. topic:: lfuns

  .. todo:: in theory this information has value in the functions doc, but there's also value to keeping it as a separate doc so that the term "lfuns" is easily discoverable in the plaintext docs.

  An lfun is a LPC function within an object which is public and can be called by other objects. In OO terms, lfuns are "methods" which you can send "messages" to.

  Calling lfuns is done by using :efun:`call_other`, which takes as arguments the object in which the lfun is to be called, the name of the lfun to be called in the object, and additional and optional arguments.

  An example looks like this::

    call_other(drink, "QueryShort");

  This call may also be written as::

    drink->QueryShort();

  This means ``call_other(object, "function", args...)`` can also be written as ``object->function(args...)``. The second form is preferred as it is easier to read.

  Some lfuns have a special meaning for the LPC driver, because they are applied by the interpreter instead from an LPC object. To distinguish those, they are called ":directory:`applied` lfuns".

  .. todo:: directory+applied is the best reference we have right now, but as I write it, it seems odd (semantically) that it isn't pointing to a term/concept/driver/language doc of some sort?

  .. seealso:: :topic:`efuns`, :directory:`efun`, :directory:`applied`, :directory:`master`, :efun:`call_other`
