.. efun:: mapping mkmapping(mixed *arr1, mixed *arr2,...)
  mapping mkmapping(struct st)

  The first form returns a mapping with indices from 'arr1' and
  values from 'arr2'... . arr1[0] will index arr2...[0], arr1[1]
  will index arr2...[1], etc. If the arrays are of unequal size,
  the mapping will only contain as much elements as are in the
  smallest array.

  The second form converts the given struct <st> into a mapping
  using the struct member names as index values.

  .. usage::

    mkmapping( ({ 1, 2 }), ({ 10, 11 }), ({ 20, 21, 22}))
      returns ([ 1:10;20, 2:11;21 ])

    struct s { int a; int *b; int c; };
    mkmapping( (<s> a: 1, b: ({ 2, 3 }), c: 3 )
      returns ([ "a":1, "b":({2,3}), "c":3 ])

  :history 3.3.433 changed: added the conversion from structs

  .. seealso:: :lang:`mappings`, :efun:`mappingp`, :efun:`m_indices`, :efun:`m_values`, :efun:`m_add`, :efun:`m_delete`, :efun:`sizeof`, :efun:`widthof`, :efun:`unmkmapping`, :efun:`to_struct`
