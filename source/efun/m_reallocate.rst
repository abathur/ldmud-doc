.. efun:: mapping m_reallocate(mapping m, int width)

  Create a new mapping with :arg:`width` values per key and fill it with the values from mapping :arg:`m`. If :arg:`m` has less than :arg:`width` values per key, the extra values in the result are set to 0. If :arg:`m` has more values per key, the extra values are ignored.

  The mapping :arg:`m` is not changed.

  .. usage::

    ::

      mapping m = ([ "foo":1;2;3, "bar":4;5;6 ])

      m_reallocate(m, 1) // returns ([ "foo":1,       "bar":4 ])
      m_reallocate(m, 4) // returns ([ "foo":1;2;3;0, "bar":4;5;6;0 ])

  :history 3.2.6 introduced: suggested by Tubmud.

  .. seealso:: :efun:`m_allocate`, :efun:`m_values`, :efun:`widthof`
