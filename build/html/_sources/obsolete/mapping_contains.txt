.. efun:: int mapping_contains(mixed &data1, ..., &dataN, map, key)
  :removed:

  If the mapping contains the key map, the corresponding values
  are assigned to the data arguments, which massed be passed by
  reference, and 1 is returned. If key is not in map, 0 is
  returned and the data args are left unchanged.
  It is possible to use this function for a 0-value mapping, in
  which case it has the same effect as :efun:`member`.

  :history 3.2.6 changed: renamed to 'm_contains()'.
  :history 3.2.9 changed: not available if driver is compiled without USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :lang:`mappings`, :efun:`member`
