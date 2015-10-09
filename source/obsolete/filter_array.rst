.. efun:: mixed *filter_array(mixed *arr, string fun, string|object ob, mixed extra, ...)
  mixed *filter_array(mixed *arr, closure cl, mixed extra, ...)
  mixed *filter_array(mixed *arr, mapping map, mixed extra, ...)
  :removed:

  Returns an array holding the items of arr filtered through
  ob->fun(element, extra, ...), the closure cl, or the mapping map.
  The function 'fun' in 'ob' resp. the closure 'cl' is called
  for each element in arr with that element as parameter. The
  extra and following parameters are in each call if given.
  The mapping 'map' is likewise indexed by each element.
  If ob->fun(arr[index], extra) returns != 0 resp.
  map[arr[index]] exists, the element is included in the
  returned array.

  If arr is not an array, an error occurs.

  The extra argument(s) are optional and must not be protected
  references like &(i[0]).
  If <ob> is omitted, or neither a string nor an object, it
  defaults to this_object().

  Since 3.2.1@36, the second arg can also be a mapping. Then
  only the elements of the array which belong to the map (as
  keys) will be returned (i.e. map[arr[index]] != 0).

  .. usage::

    ::

      int check_if_idle(object user) { return query_idle(user); }

      ...

      object *idle_users;

      idle_users = filter_array(users(), "check_if_idle");
      /* equivalent but smaller and faster */
      idle_users = filter_array(users(), #'query_idle );

    Now idle_users contains all users that have been idle for more
    than 1 second.

  :history 3.2.6 changed: obsoleted by efun filter().
  :history 3.2.9 changed: not available if driver is compiled without USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :efun:`filter`, :efun:`filter_objects`, :efun:`map`, :efun:`map_objects`
