.. efun:: int * query_mccp_stats()
  int * query_mccp_stats(object player)
  :optional:

  This efun gives you statistics about current compression of the player ( default ``this_player()`` ).

  You get an array with ``({ uncompressed bytes , compressed bytes })``. If the connection is not compressed it returns 0.

  It raises an error on not-interactive objects.

  Available only if the driver is compiled with :topic:`MCCP` enabled; :macro:`__MCCP__` is defined in that case.

  :history 3.3.447 introduced:
  :history 3.2.10 backported:

  .. seealso:: :efun:`end_mccp_compress`, :efun:`start_mccp_compress`, :efun:`query_mccp`, :concept:`mccp`
