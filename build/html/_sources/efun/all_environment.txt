.. efun:: object * all_environment()
  object * all_environment(object o)

Returns an array with all environments object <o> is in. If <o> is
omitted, the environments of the current object is returned.

If <o> has no environment, or if <o> is destructed, 0 is returned.

EXAMPLES
If o is a match in a matchbox which is in a box in a chest,
in a room, all_environment(o) will return
({ matchbox, box, chest, room }).

.. history
Introduced in LDMud 3.2.6, suggested by Tubmud.

  .. seealso:: :efun:`environment`, :efun:`all_inventory`
