.. efun:: int * query_limits()
  int * query_limits(int default)
  :include: <rtlimits.h>

  Return an array with the current runtime limits, resp. if `default` is true, the default runtime limits. The entries in the returned array are:

    int[LIMIT_EVAL]:    the max number of eval costs
    int[LIMIT_ARRAY]:   the max number of array entries
    int[LIMIT_MAPPING_SIZE]: the max number of mapping values
    int[LIMIT_MAPPING_KEYS]: the max number of mapping entries (LIMIT_MAPPING is an alias for LIMIT_MAPPING_KEYS)
    int[LIMIT_BYTE]:    the max number of bytes handled with one read_bytes()/write_bytes() call.
    int[LIMIT_FILE]:    the max number of bytes handled with one read_file()/write_file() call.
    int[LIMIT_CALLOUTS]: the number of callouts at one time.
    int[LIMIT_COST]:    how to account the current cost.
    int[LIMIT_MEMROY]:  the max. number of bytes which can be *additionally* allocated/used *per top-level execution thread*

  For all limits except LIMIT_COST a limit of '0' aka LIMIT_UNLIMITED means 'no limit'.

  The value for LIMIT_COST has these meanings:

    value > 0: the execution will cost minimum(<value>, actual cost) .

    value = 0: if the current LIMIT_EVAL is larger than the calling
               LIMIT_EVAL, the evaluation will cost only 10; otherwise
               the full cost will be accounted.

    value < 0: (-value)% of the current evaluation cost will be
               accounted; -100 obviously means 'full cost'.

  .. usage::

    ::

      query_limits()
        --> returns the current runtime limits

      query_limits(1)
        --> returns the default runtime limits

  :history 3.2.7 introduced:
  :history 3.2.9 modified: adds LIMIT_CALLOUTS
  :history 3.3.563 modified: adds LIMIT_COST
  :history 3.3.677 modified: adds LIMIT_MAPPING_KEYS, LIMIT_MAPPING_SIZE
  :history 3.5.0 modified: adds LIMIT_MEMORY

  .. seealso:: :efun:`limited`, :efun:`set_limits`
