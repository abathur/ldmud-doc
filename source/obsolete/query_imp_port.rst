.. efun:: int query_imp_port(void)
  :removed:

  Returns the port number that is used for the inter mud
  protocol.

  :history 3.2.9 changed: renamed this efun to query_udp_port(). This version
  is available if the driver is compiled with USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :efun:`send_udp`, :master:`receive_udp`
