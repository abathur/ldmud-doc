.. master:: void low_memory(int what, int limitvalue, int memory, int reservestate)
  :include: <rtlimits.h>

  This efun is called when there is a (potential) low-memory situation. Two different limits for the amount of allocated memory can be configured: a soft limit and a hard limit. If the soft limit is exceeded, the driver calls :master:`low_memory` but does nothing else. If the hard limit is exceeded, the driver calls :master:`low_memory` as well, but initiates a garbage collection directly after the call. The efun is called as well directly before a user-initiated garbage collection is started.

  :arg:`what` denotes the type of limit which was exceeded:

  .. todo:: see below re: every other discussion about defines

  - :macro:`NO_MALLOC_LIMIT_EXCEEDED`   (0)

    No limit was exceeded, but a garbage collection was requested by a call to :efun:`garbage_collection` and it will begin right after :master:`low_memory` returns.

  - :macro:`SOFT_MALLOC_LIMIT_EXCEEDED` (1)

    The soft limit was exceeded.

  - :macro:`HARD_MALLOC_LIMIT_EXCEEDED` (2)

    The hard limit was exceeded. A garbage collection will begin right after :master:`low_memory` returns.

  :arg:`limitvalue` specifies the numerical value of the limit which was exceeded. It is 0 in case of :macro:`NO_MALLOC_LIMIT_EXCEEDED`.

  :arg:`memory` specifies the amount of allocated memory right now.

  :arg:`reservestate` specifies the current state of the memory reserves of the driver. The states of the 3 different reserves are OR'ed together.

  - :macro:`USER_RESERVE_AVAILABLE`   (1)

    The user reserve is available.

  - :macro:`MASTER_RESERVE_AVAILABLE` (2)

    The master reserve is available.

  - :macro:`SYSTEM_RESERVE_AVAILABLE` (4)

    The system reserve is available.

  .. tip:: This efun might be used to inform users about the garbage collection and the expected long lag. Another possibility is to initiate a garbage collection deliberately at a suitable time (e.g. during the following night) after the soft limit was hit.

  .. note:: If in a low_memory condition when the memory reserves have been used already and they could not be re-allocated after a garbage collection :master:`slow_shut_down` is called instead of calling this function again.

  :history 3.3.719 introduced:

  .. seealso:: :efun:`debug_info`, :efun:`garbage_collection`, :master:`slow_shut_down`, :concept:`memory`
