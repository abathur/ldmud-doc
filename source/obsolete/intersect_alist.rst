.. efun:: mixed * intersect_alist(mixed * list1, mixed * list2)
  :optional:

  Does a fast set intersection on alist key vectors (NOT on full alists!).
  The operator '&' does set intersection on arrays in general.

  The function is available only if the driver is compiled with
  alist support. In that case, __ALISTS__ is defined.

  .. usage::

    ``new_list = intersect_alist(list1, list2);``

  :history 3.3 changed: made this an optional efun.

  .. seealso:: :efun:`filter_array`, :efun:`assoc`, :efun:`insert_alist`, :efun:`map_array`, :efun:`member_array`, :efun:`order_alist`, :efun:`sort_array`, :efun:`unique_array`
