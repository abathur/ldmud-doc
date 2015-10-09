.. efun:: int end_mccp_compress()
  :optional:

  This efun must be called inside an interactive player and stops
  the compression of the driver -> client traffic.

  Returns non-zero on success, and zero on a failure.

  Available only if the driver is compiled with MCCP enabled;
  __MCCP__ is defined in that case.

.. history
  Added in LDMud 3.3.447, backported to LDMud 3.2.10.

  .. seealso:: :efun:`start_mccp_compress`, :efun:`query_mccp`, :efun:`query_mccp_stats`, :concept:`mccp`
