.. efun:: mixed catch(expr, expr, ...)
  mixed catch(expr, expr, ... ; modifiers)

  Evaluate the expressions. If there is no error, 0 is returned. If there is an error, the evaluation of the expressions stops at that point, and a string with the error message is returned.

  System error messages start with a leading '*', user-defined error values (other than 0) as given to :efun:`throw` and :efun:`raise_error` are returned as they are.

  If at the time the :efun:`catch` is encountered less than :macro:`__CATCH_EVAL_COST__` eval ticks are left, a runtime error will be thrown from inside the :efun:`catch` (and thus caught like every other error) and the expressions will not be executed. The 'reserve' modifier can be used to reserve a different amount of eval ticks.

  The default behaviour of :efun:`catch` can be changed using modifiers:

    'nolog':   Normally, the caught error will be logged in the error logs for easier debugging. With this modifier, the log is suppressed.

    'publish': Normally, :master:`runtime_error` is not called for a caught error. This modifier instructs :efun:`catch` to call it nevertheless.

    'reserve :arg:`expr`': The expression has to evaluate to a number greater than 0 and is used to determine the amount of eval ticks to reserve, instead of the default of :macro:`__CATCH_EVAL_COST__`. The minimum required are 2 * :macro:`__MASTER_EVAL_COST__`.

  :efun:`catch` itself is not expensive as far as execution time is concerned: it is about the same as a intra-object function call.

  :efun:`throw` is not very expensive either, but does include the internal cleanup of several structures.

  Real runtime errors on the other hand are expensive regardless of whether they are caught or not, as they include the generation of the stack backtrace.

  :efun:`catch` is not _really_ an efun but a compiler directive.

  .. usage::

    This example demonstrates how to attempt to clone an object, but write a message if an error is encountered::

      object obj;
      string err;
      if (err = catch(obj = clone_object("/foo/bar/baz")))
         write("Cannot clone object, reason:"+err"+\n");

  :history 3.2.9 changed: introduced the 'nolog' :efun:`catch` as experimental feature.
  :history 3.2.10 changed: implemented 'nolog' as official form and added 'publish'.
  :history 3.3.559 changed: moved the check regarding :macro:`__CATCH_EVAL_COST__` inside the :efun:`catch`.
  :history 3.3.560 changed: added the 'reserve' modifier.

  .. seealso:: :efun:`throw`, :efun:`raise_error`, :topic:`predefined`, :master:`runtime_error`
