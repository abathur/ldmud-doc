.. efun:: int m_sizeof(mapping map)
  :removed:

  Returns the number of indices in mapping 'map'.
  This function is in fact an alias for sizeof().

  :history 3.2.9 changed: not available if driver is compiled without USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :efun:`mappingp`, :efun:`mkmapping`, :efun:`m_indices`, :efun:`m_values`, :efun:`m_delete`, :efun:`sizeof`, :efun:`widthof`.
