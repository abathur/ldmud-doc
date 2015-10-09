.. hook:: H_ERQ_STOP

  :arg closure value: void <closure>()

  Optional hook to notify the mudlib about the termination of
  the erq demon. Hook setting may be any closure.

  The closure is called without arguments and may do whatever it
  likes to clean-up after the erq.

  .. history

  .. seealso:: :concept:`hooks`
