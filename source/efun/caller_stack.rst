.. efun:: object * caller_stack()
  object * caller_stack(int add_interactive)

  Returns an array of the previous objects who caused the :efun:`call_other` to :efun:`this_object`. ``previous_object(i)`` equals ``caller_stack()[i]``.

  If you pass the optional argument :arg:`add_interactive` (as true value) ``this_interactive()`` is appended to the array, or 0 if there is no current interactive.

  .. note:: calls to 'alien lfun closures' (see :efun:`symbol_function`) generate two entries on the stack if the bound object differs from the closure object: the first is for the bound object, the second for the closure object.

  .. usage::

    interactive object A enters a command which causes a call to a function in object B, that one calls a function in object C and that, in turn, in object D

    If D now calls ``caller_stack()`` the result would be: ``({C,B})``. If it calls ``caller_stack(1)`` the result is: ``({C,B,A})``.

  .. todo:: not a good use of usage section; no actual code example

  :history 3.2.6 introduced: suggested by Tubmud.

  .. seealso:: :efun:`caller_stack_depth`, :efun:`previous_object`, :efun:`this_interactive`, :efun:`call_other`
