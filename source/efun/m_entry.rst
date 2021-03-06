.. efun:: mixed * m_entry(mapping map, mixed key)

  Query the mapping :arg:`map` for the entry for :arg:`key` and return all its values in one array.

  If :arg:`map` does not contain :arg:`key`, 0 is returned.

  .. note:: :efun:`m_add` can be used to add all values for an entry at once.

  .. usage::

    ::

      mapping m = ([ 1:"foo":-1, 2:"bar":-2 ]);

      m_entry(m, 0) // 0
      m_entry(m, 1) // ({ "foo", -1 })

  :history 3.2.10 introduced:

  .. seealso:: :efun:`m_add`, :efun:`m_contains`, :type:`mapping`, :efun:`member`
