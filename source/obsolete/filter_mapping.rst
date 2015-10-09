.. efun:: mapping filter_mapping(mapping, string func, string|object ob, ...)
  mapping filter_mapping(mapping, closure cl, ...)
  :removed:

  ob->func() is called resp. cl applied to every element in the
  mapping, with first argument being the key of the
  element, and then the extra args that were given to
  filter_mapping (these args must not be protected references like
  &(i[0]). If the function returns true, the element is
  element, and then the extra args that were given to
  added to the result mapping. ob can also be a file_name of an
  object.

  If <ob> is omitted, or neither a string nor an object, it
  defaults to this_object().

  :history 3.2.6 changed: renamed to filter_indices().
  :history 3.2.9 changed: not available if driver is compiled without USE_DEPRECATED.
  :history 3.3 removed:

  .. seealso:: :efun:`filter`, :efun:`map`, :efun:`map_indices`, :efun:`walk_mapping`, :efun:`member`, :efun:`m_contains`
