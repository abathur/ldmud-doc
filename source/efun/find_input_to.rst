.. efun:: int find_input_to(object player, string fun)
  int find_input_to(object player, closure fun)
  int find_input_to(object player, object fun)
  int find_input_to(object player, object ob, string fun)

  Find the input_to most recently added to the interactive :arg:`player` object matching the :arg:`fun` argument:

  - :arg:`fun` is a string: the input_to functionname has to match
  - :arg:`fun` is an object: the object the input_to function is bound to has to match
  - :arg:`fun` is a closure: the input_to closure has to match.
  - :arg:`ob` and :arg:`fun` are given: both the object and the functionname have to match

  .. todo:: note that the text parser doesn't catch all of the arg refs in the list above...

  Return -1 if not found, or the position in the input_to stack (0 being _least_ recently added input_to).

  :history 3.2.9 introduced:

  .. seealso:: :efun:`input_to`, :efun:`input_to_info`, :efun:`remove_input_to`, :efun:`query_input_pending`
