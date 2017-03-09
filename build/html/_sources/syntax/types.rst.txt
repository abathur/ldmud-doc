.. topic:: types

  Variables can have the following types:

  :type:`int`
    An integer.

  :type:`string`
    A text string.

  :type:`status`
    .. obsolete:: status was planned to be an optimized boolean format, but this was never actually implemented. status does work; however, since it is only an alias for type 'int', just use int.

  :type:`object`
    Pointer to an object. Objects are always passed by reference.

  :type:`array`
    Pointer to a vector of values, which could also be an alist. Arrays take the form ``({ n1, n2, n3 })`` and may contain any type or a mix of types. Arrays are always passed by reference.

    .. note:: the size of arrays in LPC *can* be changed at run-time.

  :type:`mapping`
    An 'associative array' consisting of values indexed by keys. The indices can be any kind of datatype. Mappings take the form ``([ key1: value1, key2: value2 ])``. By default, mappings are passed by reference.

  :type:`closure`
    References to executable code, both to local functions, efuns and to functions compiled at run-time ("lambda closures").

  :type:`symbol`
    Identifier names, which in essence are quoted strings. They are used to compute lambda closures, e.g. instead of ``({..., 'ident, ... })`` you can write declare a 'symbol' variable foo, compute a value for it, and then create the closure as ``({ ..., foo, ... })``

  :type:`float`
    A floating-point number.

  :type:`mixed`
    A variable allowed to take a value of any type (int, string, object, array, mapping, float or closure).

  :type:`struct`
    A collection of values. See :type:`struct`.

  :syntax:`union`
    A range of types, either of which the variable can contain at runtime. See :syntax:`union`.

  .. todo:: decide where the below belong

  .. type:: unknown

    An unusable (documentation-only) meta-type indicating that a function's return type is undefined.

  .. type:: null

    Indicates a function that returns no value.

  All uninitialized variables have the value 0.

  The type of a variable is really only for documentation. Unless you define :pragma:`strong_types` or :pragma:`rtt_checks`, variables can actually be of any type and has no effect at all on the program. However, it's extremely bad style to declare one type but use another, so please try to avoid this.

  .. todo:: I think the above needs to shift in 3.5

  .. seealso:: :type:`array`, :type:`mapping`, :type:`closure`, :type:`struct`, :syntax:`union`, :efun:`typeof`, :efun:`get_type_info`, :concept:`inheritance`, :syntax:`pragma`, :syntax:`modifiers`, :syntax:`escape`
