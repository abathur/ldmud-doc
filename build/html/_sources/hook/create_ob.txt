.. hook:: H_CREATE_OB

  :arg string value: void <name> (0)
  :arg closure value: int <closure> ( void )
  :arg closure value: int <closure> (object obj_to_init)

  Optional hooks to initialize an explicitly loaded object/blueprint after creation. Hook setting can be unbound lambda closures or the name of the function (static or public) to call in the object.

  If the hook is a closure expecting an argument, it is bound to the current object and called with the created object as argument. If the hook is a closure without arguments, it is bound to the object to be initalized and called.

  If the result of the closure call is a non-zero number, it is used as the interval to wait before the first reset(), else the default interval computed from TIME_TO_RESET is used.

  If the hook is defined as the name of an lfun in the object, it is called in the object with 0 as argument and any result is ignored.

  :history 3.2.10 changed: allowed static functions to be given by name.

  .. seealso:: :concept:`hooks`, :hook:`create_super`, :hook:`create_clone`
