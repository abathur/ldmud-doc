.. efun:: mixed * insert_alist(mixed key, mixed data..., mixed * alist)
  int insert_alist(mixed key, mixed * keys)
  :optional:

  1. Form: Alist Insertion

     The <key> and all following <data> values are inserted
     into the <alist>. If an entry for <key> already exists
     in the list, just the data values are replaced. The number
     of <data> values must match the number of data arrays
     in the alist, naturally.

     Result is the updated <alist>.

  2. Form: Key Insertion

     Insert the <key> into the (ordered) array of <keys>, so that
     subsequent assoc()s can perform quick lookups. Result is the
     index at which <key> was inserted (or already found).

     .. note:: when working with string keys, the index might no longer
       be valid after the next call to insert_alist().

  Complexity: O(lg(n) + a*n) where n is the number of keys and
  s is a very small constant (for block move);

  The function is available only if the driver is compiled with
  alist support. In that case, __ALISTS__ is defined.

  :history 3.3 changed: made this an optional efun.

  .. seealso:: :lang:`alists`, :efun:`assoc`, :efun:`order_alist`

