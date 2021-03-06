pragma {#driver_syntax_pragma}
==============================
The preprocessor directive `#pragma` can be used to select several compilation options. Multiple options can be selected in one `#pragma` directive by separating them with commas.

no_clone
The blueprint object can't be cloned.

no_inherit
The program can't be inherited.

no_shadow
The program can't be shadowed (similar to declaring all functions as >>:modified:`nomask`<<).

init_variables
Clone variables are initialized by `__INIT()`.

share_variables
Clone variables are initialized from the blueprint.

weak_types
no type checking (this is the default).

strict_types
all functions must be declared with argument prototypes, and the return values of efun::call_other() must be cast.

strong_types
all functions must be declared with complete types of return value and parameters.

save_types
the declaration data is kept after compilation and checked at runtime. This is important for type-safe inheritance.

rtt_checks
runtime checks during execution of this program will be enabled. The interpreter will check for correct datatypes of arguments on function calls. (Later it will include checks upon assignments.) Don't confuse this with @ref driver_syntax_pragma "strong_types" / @ref driver_syntax_pragma "strict_types", they only check at compile time. @ref driver_syntax_pragma "strong_types" / @ref driver_syntax_pragma "strict_types" is seriously recommended. This pragma implicitly enables save_types as well.

no_rtt_checks
disable runtime type checks for this program (default).

pedantic
Certain warnings are treated as errors:

- failure to pass enough arguments to simul efuns

sloppy
Turns off pedantic (the default).

range_check
Use of questionable ranges (ranges of negative sizes, or with bounds beyond the array's size) cause a runtime warning.

no_range_check
Turns off range_check (the default).

warn_deprecated
Use of deprecated efuns or indexing operations causes the compiler to issue a warning (the default).

no_warn_deprecated
Turns off warn_deprecated.

warn_empty_casts
A cast of a value to its own type generates a warning (the default). Exception are casts to type 'mixed'.

no_warn_empty_casts
Turns off warn_empty_casts.

warn_missing_return
Warn if a value-returning function is missing a return statement (the default). If possible, the driver will try to detect this at compile time; otherwise a runtime warning will be generated when the function is executed. The check applies only to functions with a declared return type other than 'void'.

no_warn_missing_return
Turn off warn_missing_return.

warn_function_inconsistent
If an inherited function is overloaded with inconsistent return types or arguments, a warning is generated; or if pragma_pedantic is in effect, an error. By default this is active.

no_warn_function_inconsistent
An inherited function can be overloaded with inconsistent return types or arguments, as long as pragma_pedantic is not in effect.

This pragma is meant to easen the adaption of legacy mudlib code - in general one should fix the warnings, not turn them off.

When an object is compiled with type testing (@ref driver_syntax_pragma "strict_types"), all types are saved of the arguments for that function during compilation. If @ref driver_syntax_pragma "save_types" is specified, then the types are saved even after compilation, to be used when the object is inherited.

The following two pragmas are available if the driver was compiled with DEBUG and TRACE_CODE options:

set_code_window
Sets an offset to the current program writing position. Use this <em>before</em> a piece of code where you want to check to what bytecodes it is compiled.

show_code_window
shows some bytes starting at or near the last point set_code_window was called.

@usage{
~~~{.c}
#pragma strict_types
#pragma no_clone, no_inherit

~~~

}

@history{
changed (3.2.7) -- added local_scopes, no_local_scopes, no_clone and no_inherit.
changed (3.2.8) -- added weak_types, pedantic and sloppy.
changed (3.2.9) -- allowed to specify multiple pragmas in one directive.
changed -- added no_warn_deprecated and warn_deprecated.
changed (3.2.10) -- added no_warn_empty_casts and warn_empty_casts.
changed -- #pragma xxx_types in an included file now remain active when processing returns to the including file.
changed (3.2.11) -- added no_warn_empty_casts and warn_function_inconsistent.
changed (3.3.378) -- added init_variables, share_variables.
changed (3.3.357) -- added no_warn_empty_casts and warn_missing_return.
changed (3.3.646) -- added no_warn_empty_casts and range_check.
changed (3.5.0) -- removed combine_strings and no_combine_strings.
changed -- removed local_scopes and no_local_scopes.
changed -- removed verbose_errors (making its behaviour mandatory).
changed -- enabled warn_deprecated by default.
}

@see @ref driver_topics_inheritance "inheritance", @ref driver_master_initialisation "initialisation", @ref driver_syntax_operators "operators"
