.. applied:: int drop(void)
  int drop(int silently)
  :deprecated:

  In compat mode this lfun is used by :efun:`transfer`.

  It is called to check if an object wants to be moved out of the inventory of a living object. :applied:`drop` should return 1 to prevent dropping. This is the opposite of the :applied:`get` function. That is because if :applied:`drop` is not defined, it will always be possible to drop an object.

  If the object self-destructs when :applied:`drop` is called, be sure to return 1, as the destructed item surely not can be dropped.

  Most compat mode LPC libraries to define one argument for drop. If silently is true, no messages should be written.

  :history 3.3 deprecated: because :efun:`transfer` has been deprecated.

  .. seealso:: :efun:`transfer`
