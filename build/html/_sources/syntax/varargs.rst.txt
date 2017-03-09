.. keyword:: varargs
  varargs function: [ modifier ] [ varargs ] [ return type ] function( args...)
    : varargs void fun (string arg1, int arg2, int arg3)
  varargs parameter: (... varargs [type...] argname)
    : void fun (string arg1, int arg2, varargs int * arg3)

  .. commenting out for now .. modifier:: varargs

  A function uses "varargs" (short for "variable arguments") so that it can be called with less or more arguments than formally specified.

  The proper order to define a function call is::

    [ modifier ] [ varargs ] [ return type ] function( args...)

  Any other order will result in an error.

  .. usage::

    Given a function definition like this::

      void fun (string arg1, int arg2, int arg3)

    ``fun()`` has to be called with exactly three parameters: one string and two integers.

    If the function is defined as::

      varargs void fun (string arg1, int arg2, int arg3)

    it is possible to call the function with just arg1, or arg1 and arg2. The remaining unspecified arguments (arg2 and arg3, resp. arg3) are in these cases assumed to be 0.

    To pass _more_ arguments than specified, the function's last parameter must be defined as::

      void fun (string arg1, int arg2, varargs int * arg3)

    This allows ``fun()`` to be called with two or more arguments. These "extra" arguments (in this case, all but the first two) are collected into an array which is then passed as arg3. For example::

      fun("foo", 1)       // arg3 == ({ })
      fun("foo", 1, 2)    // arg3 == ({ 2 })
      fun("foo", 1, 2, 3) // arg3 == ({ 2, 3 })

    The type of the varargs argument must be an array of the expected type (int*, object*, string*, ...). Only integers are allowed in the above example, but you could accept arguments of any kind by defining the parameter as 'varargs mixed' or 'varargs mixed*'.

    .. todo:: should flatten be a topic or a glossary entry?

    There are two ways to 'flatten' the received argument array in your own function calls. You can use :efun:`apply`; e.g.::

      apply(#'call_out, "bar", 1, arg3)

    or the 'flatten arguments' operator::

      call_out("bar", 1, arg3...)

    The two varargs variants can of course be combined to define a function which may be called with any number of arguments::

      varargs void fun (string arg1, int arg2, varargs int* arg3)

  :history 3.2.1@132 changed: Added ability to pass more arguments than formally specified (previously, excess arguments were silently ignored).

  .. seealso:: :syntax:`pragma`, :efun:`apply`, :syntax:`modifiers`
