.. efun:: int get_eval_cost()

  Returns the remaining evaluation cost the current
  execution (the current command) may use up.

  It starts at a driver given high value and
  is reduced with each executed statement.

.. history
  The initial value was made available as macro in LDMud 3.2.6.

  .. seealso:: :efun:`rusage`, :efun:`command`, :efun:`query_limits`
