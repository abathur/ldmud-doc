.. efun:: int member_array(mixed item, mixed *arr)
  int member_array(mixed item, string arr)
  :removed:

  Returns the index of the first occurence of item in array arr,
  or occurence of a character in a string. If not found, then -1
  is returned.

  If you want to search through an alist, use assoc() because
  member_array() is good for unsorted but assoc() is faster for
  sorted arrays.

  :history 3.3 removed: superseded by efun:`member`

  .. seealso:: :efun:`member`, :lang:`alists`, :lang:`mappings`, :efun:`assoc`, :efun:`slice_array`
