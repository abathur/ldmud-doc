.. efun:: void destruct(object ob)

  Completely destroy and remove object ob (if not already done so). After the call to :efun:`destruct`, no global variables will exist any longer, only local ones, and arguments.

  If an object self-destructs, it will not immediately terminate execution. If the :efun:`this_object` will be called by the destructed object, the result will be 0. Furthermore, all calls to other objects and to simul-efuns will be ignored, instead the driver will return 0 als 'call' result.

  To keep things consistent, most mudlibs frown upon the destruction of other objects, and instead demand call_others to a specific lfun in the object to destruct (traditionally named "remove"). This will then ensure correct update of e.g. weights, volumes etc. Additionally (or instead), :master:`prepare_destruct` can be used for this 'cleanup' functionality.

  The interpreter does not really destruct the object immediately, but marks it as deleted, removes it from the list of all objects, and puts it onto a list of to-be-destructed objects. The actual freeing occurs only when all references to a destructed object have gone. Thus it is possible, that an object occupies memory long after it has been destructed, although the object is not visible anywhere anymore from outside.

  .. usage::

    To force destruction after giving an object a chance to clean up and destruct itself::

      ob->remove();
      if(ob)        // still there, probably ob does not provide remove()
         destruct(ob);

  :history 3.2.7 changed: accepts destructed objects as argument, too.

  .. seealso:: :efun:`clone_object`, :applied:`remove`, :master:`prepare_destruct`
