.. efun:: object * filter_objects(object *arr, string fun, mixed extra, ...)

  Similar to ``filter_array()`` but calls ``arr[n]->fun(extra, ...)``. If the call returns != 0, the object arr[n] ist included in the returned array.

  .. note:: 0-entries in arr are ignored.

  .. todo:: mention of filter_array is dated, rewrite intro?

  .. seealso:: :efun:`filter`, :efun:`map`, :efun:`map_objects`
