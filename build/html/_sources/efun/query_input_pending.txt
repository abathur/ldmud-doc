.. efun:: object query_input_pending(object ob)

  If ob is interactive and currently has an input_to() pending,
  the object that has called the input_to() is returned,
  else 0.

  .. seealso:: :efun:`input_to`, :efun:`find_input_to`, :efun:`input_to_info`, :efun:`remove_input_to`
