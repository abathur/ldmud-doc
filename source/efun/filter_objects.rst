.. efun:: object * filter_objects(object *arr, string fun, mixed extra, ...)

  Similar to filter_array() but calls arr[n]->fun(extra, ...).
  If the call returns != 0, the object arr[n] ist included in
  the returned array.
  0-entries in arr are ignored.

  .. seealso:: :efun:`filter`, :efun:`map`, :efun:`map_objects`
