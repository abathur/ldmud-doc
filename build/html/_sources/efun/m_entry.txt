.. efun:: mixed * m_entry(mapping map, mixed key)

Query the mapping <map> for the entry for <key> and return all
its values in one array.

If <map> does not contain <key>, 0 is returned.

Note: the efun m_add() can be used to add all values for an entry
at once.

EXAMPLES
mapping m = ([ 1:"foo":-1, 2:"bar":-2 ]);

m_entry(m, 0) -> 0
m_entry(m, 1) -> ({ "foo", -1 })

.. history
Introduced in LDMud 3.2.10.

  .. seealso:: :efun:`m_add`, :efun:`m_contains`, :lang:`mappings`, :efun:`member`
