lfuns {#driver_topics_lfuns}
============================
An lfun is a LPC function within an object which is public and can be called by other objects. In OO terms, lfuns are "methods" which you can send "messages" to.

Calling lfuns is done by using efun::call_other(), which takes as arguments the object in which the lfun is to be called, the name of the lfun to be called in the object, and additional and optional arguments.

An example looks like this:

~~~{.c}
call_other(drink, "QueryShort");

~~~
This call may also be written as:

~~~{.c}
drink->QueryShort();

~~~
This means `call_other(object, "function", args...)` can also be written as `object->function(args...)`. The second form is preferred as it is easier to read.

Some lfuns have a special meaning for the LPC driver, because they are applied by the interpreter instead from an LPC object. To distinguish those, they are called ">>:directory:`applied`<< lfuns".

@see @ref driver_topics_efuns "efuns", efun::call_other()
