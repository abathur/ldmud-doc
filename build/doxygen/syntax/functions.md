functions {#driver_syntax_functions}
====================================
Functions are named blocks of code which are be called with a number of argument values, and which return a result value to the caller.

Functions are defined in an object and are also known as "local funs" or short "lfuns".

## Defining A Function #

A function definition takes the form:

~~~{.c}
<modifiers> <type> name ( <arguments> ) {
  statements...
}

~~~
The parts in detail:

`<modifiers>`
can be any one of "static", "private", "public" and "protected" (see @ref driver_syntax_modifiers "modifiers"), optionally combined with "varargs" (see @ref driver_syntax_varargs "varargs") and/or "nomask". If not specified, the function behaves as if it was specified as "public", but this visibility can be restricted in derived object through non-public inheritance.

`<type>`
is the type of the result returned by the function. If specified as "void", the function is compiled to return the value 0 under all circumstances. If not specified, the type is assumed to be "mixed", furthermore typechecking is disabled for this function.

`name`
is the name of the function, e.g. "short", or "Nice_Try", under which it is made known.

`<arguments>`
is a list of variable definitions in the normal `<type> <name>` style, separated by comma. Examples:

- `()` takes no arguments
- `(int a)` takes one integer argument
- `(mixed a, object *b)` takes two arguments, one arbitrary type, one array of objects

`{ statements... }`
defines the code for this function. This is a normal block (see @ref driver_syntax_block "block") and as such can define its own local variables.

## Declaring A Function #

A function declaration makes the name and type of a function known to the compiler with the assertion that the code for this function will be provided "elsewhere".

[<modifier>...] [<type>] <name> ([<argument>...]);: `[<modifier>...] [<type>] <name> ([<argument>...]);`
The form is:

~~~{.c}
<modifiers> <type> name ( <arguments> );

~~~
Typical uses are:

- to declare in advance functions which are called before they can be defined; for example if the applied::create() function of an object calls other functions which are defined after the applied::create().
- to declare functions which will be provided by an inheriting object.

Calling a declared but undefined function results in a runtime error.

## Calling A Function #

Functions in other objects are called with efun::call_other(), which can be shortened to `->`:

~~~{.c}
ob->fun(a, b, c)
call_other(ob, "fun", a, b, c)

~~~
@par note: See the entry @ref driver_hook_default_method "H_DEFAULT_METHOD" in @ref driver_hook_overview "hook" for a modification of this behaviour.

Functions in the same object are called just by writing their name, followed by the arguments in parenthesis:

~~~{.c}
short()
compute(a)
do_that(a, "foo")

~~~
Array function arguments can be 'flattened' with the '...' operator. For example:

~~~{.c}
mixed * m = ({ "foo", "bar" });
fun(m..., 1);

~~~
will be executed as:

~~~{.c}
fun("foo", "bar", 1);

~~~
If the number of values passed to the function does not match the number of expected arguments (and if type checking is not enabled), the driver will perform the necessary adaption at call time: excess values are ignored, missing values are substituted by the number 0. The values passed to the called function are massaged by the driver to match the argument list.

## Functions And Inheritance #

A "public" or "protected" (== "static") function defined in one object is also visible in all inheriting objects. The exception from this rule is when an inheriting child redefines ("overloads") the inherited function with its own. When compiling with type checking, the argument list of the redefined function has to match the original one.

When a function is called, the driver looks for the function first in the object called, and if not found there, then in the inherited objects.

To explicitely call an inherited function (useful when a redefining functions wants to use the original one), the `::` operator is used:

~~~{.c}
::create()
::compute(a)

~~~
The named function is searched only in the inherited objects, and the first found is used.

If the function is inherited from several objects and a specific one is to be called, the "::" can be extended to contain the partial or full name of the inherited object:

~~~{.c}
inherit "/obj/cooker";
inherit "/obj/container";

tainer::create()
container::create()
"tainer"::create()
"container"::create()
"obj/container"::create()
"/obj/container"::create()

~~~
all of these call `create()` in the container inherit. Note that the name given to the `::` operator is matched against the ends of the inherited names.

One special form of this call is

~~~{.c}
efun::find_object()

~~~
which bypasses any redefinition of an efun (here efun::find_object()) and directly calls the efun itself. This is only possible for efun-redefinitions which do not use the "nomask" modifier.

Additionally, a call to a function inherited from several objects can be instructed to call _all_ inherited functions through the use of the wildcards "*" (match any number of arbitrary characters) and "?" (match one arbitrary character)

~~~{.c}
inherit "/obj/cooker";
inherit "/obj/container";

"*"::create()
"co*"::create()
"*er"::create()

~~~
all of these call both inherited `create()` functions. The function called this way must not take arguments, and the single results from all calls are combined into one array used as final result. If there is no such function inherited at all, the statement will just return an empty array.

@see @ref driver_syntax_types "types", @ref driver_syntax_modifiers "modifiers", @ref driver_syntax_varargs "varargs", @ref driver_syntax_references "reference", efun::call_other(), efun::call_out()
