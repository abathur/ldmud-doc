.. syntax:: pragma
  #pragma <name>
  #pragma <name>[, <name>...]
  :topics: preprocessor

  The preprocessor directive ``#pragma`` can be used to select several compilation options. Multiple options can be selected in one ``#pragma`` directive by separating them with commas.

  .. pragma:: no_clone

    The blueprint object can't be cloned.

  .. pragma:: no_inherit

    The program can't be inherited.

  .. pragma:: no_shadow

    The program can't be shadowed (similar to declaring all functions as :modified:`nomask`).

  .. pragma:: init_variables

    Clone variables are initialized by ``__INIT()``.

    .. todo:: link above to the initialisation doc?

  .. pragma:: share_variables

    Clone variables are initialized from the blueprint.

  .. pragma:: weak_types

    no type checking (this is the default).

  .. pragma:: strict_types

    all functions must be declared with argument prototypes, and the return values of :efun:`call_other` must be cast.

  .. pragma:: strong_types

    all functions must be declared with complete types of return value and parameters.

  .. pragma:: save_types

    the declaration data is kept after compilation and checked at runtime. This is important for type-safe inheritance.

  .. pragma:: rtt_checks

    runtime checks during execution of this program will be enabled. The interpreter will check for correct datatypes of arguments on function calls. (Later it will include checks upon assignments.) Don't confuse this with :pragma:`strong_types` / :pragma:`strict_types`, they only check at compile time. :pragma:`strong_types` / :pragma:`strict_types` is seriously recommended. This pragma implicitly enables save_types as well.

    .. todo:: reduce the pragma ref repetition above

  .. pragma:: no_rtt_checks

    disable runtime type checks for this program (default).

  .. pragma:: pedantic

    Certain warnings are treated as errors:

    - failure to pass enough arguments to simul efuns

  .. pragma:: sloppy

    Turns off pedantic (the default).

  .. pragma:: range_check

    Use of questionable ranges (ranges of negative sizes, or with bounds beyond the array's size) cause a runtime warning.

  .. pragma:: no_range_check

    Turns off range_check (the default).

  .. pragma:: warn_deprecated

    Use of deprecated efuns or indexing operations causes the compiler to issue a warning (the default).

  .. pragma:: no_warn_deprecated

    Turns off warn_deprecated.

  .. pragma:: warn_empty_casts

    A cast of a value to its own type generates a warning (the default). Exception are casts to type 'mixed'.

  .. pragma:: no_warn_empty_casts

    Turns off warn_empty_casts.

  .. pragma:: warn_missing_return

    Warn if a value-returning function is missing a return statement (the default). If possible, the driver will try to detect this at compile time; otherwise a runtime warning will be generated when the function is executed. The check applies only to functions with a declared return type other than 'void'.

  .. pragma:: no_warn_missing_return

    Turn off warn_missing_return.

  .. pragma:: warn_function_inconsistent

    If an inherited function is overloaded with inconsistent return types or arguments, a warning is generated; or if pragma_pedantic is in effect, an error. By default this is active.

  .. pragma:: no_warn_function_inconsistent

    An inherited function can be overloaded with inconsistent return types or arguments, as long as pragma_pedantic is not in effect.

    This pragma is meant to easen the adaption of legacy mudlib code - in general one should fix the warnings, not turn them off.

  When an object is compiled with type testing (:pragma:`strict_types`), all types are saved of the arguments for that function during compilation. If :pragma:`save_types` is specified, then the types are saved even after compilation, to be used when the object is inherited.

  The following two pragmas are available if the driver was compiled with DEBUG and TRACE_CODE options:

  .. pragma:: set_code_window

    Sets an offset to the current program writing position. Use this *before* a piece of code where you want to check to what bytecodes it is compiled.

  .. pragma:: show_code_window

    shows some bytes starting at or near the last point set_code_window was called.

  .. usage::

    ::

      #pragma strict_types
      #pragma no_clone, no_inherit

  :history 3.2.7 changed: added local_scopes, no_local_scopes, :pragma:`no_clone` and :pragma:`no_inherit`.
  :history 3.2.8 changed: added :pragma:`weak_types`, :pragma:`pedantic` and :pragma:`sloppy`.
  :history 3.2.9 changed: allowed to specify multiple pragmas in one directive.
  :history 3.2.9 changed: added :pragma:`no_warn_deprecated` and :pragma:`warn_deprecated`.
  :history 3.2.10 changed: added :pragma:`no_warn_empty_casts` and :pragma:`warn_empty_casts`.
  :history 3.2.10 changed: ``#pragma xxx_types`` in an included file now remain active when processing returns to the including file.
  :history 3.2.11 changed: added :pragma:`no_warn_empty_casts` and :pragma:`warn_function_inconsistent`.
  :history 3.3.378 changed: added :pragma:`init_variables`, :pragma:`share_variables`.
  :history 3.3.357 changed: added :pragma:`no_warn_empty_casts` and :pragma:`warn_missing_return`.
  :history 3.3.646 changed: added :pragma:`no_warn_empty_casts` and :pragma:`range_check`.
  :history 3.5.0 changed: removed combine_strings and no_combine_strings.
  :history 3.5.0 changed: removed local_scopes and no_local_scopes.
  :history 3.5.0 changed: removed verbose_errors (making its behaviour mandatory).
  :history 3.5.0 changed: enabled :pragma:`warn_deprecated` by default.

  .. seealso:: :topic:`inheritance`, :topic:`initialisation`, :concept:`objects`, :lang:`operators`
