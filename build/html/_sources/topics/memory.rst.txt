.. topic:: memory swapping
  :name: memory

  .. todo:: This is out of date. Also document the relation with reset

  .. misleading:: This document is out of date.

  (Collected from the Changelogs of the driver source)

  The swapping algorithm has been changed. A test is done for every object, comparing to a time stamp. If the object hasn't been touched for a while, it could be subject for swapping. Here comes the new thing: the function :hook:`H_CLEAN_UP` will be called in the object. If the object still remains, the old swapping algorithm will continue. That means that objects that would never be subject to swapping (cloned objects) now have a chance to self-destruct. It also means that rooms that contains no important data can self-destruct. Self-destruction saves more memory than swapping, as swapping only frees the program code, while self-destruction also frees the internal object representation.

  The call of :hook:`H_CLEAN_UP` has been modified. There is a constant in :file:`config.h` that defines how long time until clean_up is called in an object. This call is independent of :hook:`H_RESET` and swapping. It is recommended that the swapping time is something short, like 10 minutes to 30 minutes, while the time to `clean_up` is longer.

  Fixed several bugs in the swap/reset/clean_up logic. Recommended values are that the swap time is short (less than 30 minutes), and that reset time is medium (aprox 60 minutes), and that time to clean_up is long (greater than 1.5h hours). Any feedback of how to best tune these values are welcome. The call of reset will be done once, and not yet again until the object has been touched. This enables reset'ed objects to stay swapped out. If you have a mudlib that has no objects that define `clean_up`, then you may better define this time as 0, which means never call clean_up (and thus never swap the object in needlessly). A well implemented usage of clean_up is better than the swap algorithm, as even cloned objects can be cleaned up and a self destruction is more efficient than swapping (memory wise).

  Changed mechanism of calling :hook:`H_CLEAN_UP` slightly. Only objects that define the function will be called. And, only :hook:`H_CLEAN_UP` that returns non-zero will be called again. This will minimize calls of :hook:`H_CLEAN_UP`, while still costing little to maintain.

  :hook:`H_CLEAN_UP` now gets a flag as argument, which will be non-zero if the the program of this object is used for inheritance by other objects.

  .. seealso:: :applied:`clean_up`, :master:`slow_shut_down`, :master:`quota_demon`, :master:`low_memory`, :efun:`garbage_collection`
