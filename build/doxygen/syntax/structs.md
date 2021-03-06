structs {#driver_syntax_structs}
================================
declare     ::= struct struct_name;
define      ::= struct name (parent) {int one;};
construct   ::= (<struct_name>)
              (<struct_name> 1)
              (<struct_name> one: 1)
              test (* comment *) test
struct_name ::= beeps

declare     ::= struct struct_name;
define      ::= struct name (parent) {int one;};
construct   ::= (<struct_name>)
              (<struct_name> 1)
              (<struct_name> one: 1)
              test (* comment *) test
struct_name ::= beeps

Structs are, next to arrays and mappings, a way to group a collection of values together. A struct holds a fixed number of values, called 'members', and allows to access them by their given name. The name is resolved when the LPC code is compiled, making struct member access as fast as array member access.

Structs are passed by reference. @ref struct_name

## DEFINING #

A new struct type has to be @ref defined at the top level of an object. For example:

~~~{.c}
struct Foo {
  int        one, *two;
  struct Bar three;
};

~~~
defines the new struct 'Foo' with three members: integer 'one', integer array 'two', and struct Bar 'three'

It is possible to 'inherit' structs from each other. Given above definition of struct Foo, the following definition

~~~{.c}
struct Quux (Foo) {
  int four;
};

~~~
is equivalent to the definition:

~~~{.c}
struct Quux {
  int        one, *two;
  struct Bar three;
  int four;
};

~~~
The usual visibility modifiers apply, e.g.

~~~{.c}
protected struct Bang {...};

~~~
struct definitions are promoted through inheritance like functions, with the difference that all structs live in the same flat namespace. This means: a struct defined in a program is visible in _all_ inherited programs, regardless of how deep the inheritance is nested. This also means that in one program there must not be two structs, inherited or not, with the same name.

To @ref declare a struct without defining it, write:

~~~{.c}
struct Quux;

~~~
This notation is useful if you have two structs referencing each other:

~~~{.c}
struct Quux;

struct Bar {
  struct Quux quux;
};
struct Quux {
  struct Bar bar;
};

~~~

## CREATING #

To use a struct, its definition must be visible - either because it is defined in the object compiled, or it has been inherited.

@par note: #include'ing structs does not what you think it does: in LPC it constructs a new struct type whereever it is included.

A variable to hold a struct is defined like this:

~~~{.c}
struct Foo var;

~~~
and similar for function arguments:

~~~{.c}
void fun (struct Foo arg)

~~~
Just writing 'struct Foo var' however does not _create_ a struct, it just creates a variable capable of holding one. To assign a value to the variable upon creation, assign it with a struct value, either from another variable or from a literal struct:

~~~{.c}
struct Foo var = (<Foo>);

~~~
Literal structs are written using `(<>)` as delimiters:

`(<Foo>)`
creates an empty instance of struct Foo

`(<Foo> 1, ({ 2 }), bar)`
creates an instance of struct Foo, and assigns `1` to member 'one', `({ 2 })` to member 'two', and the content of variable `bar` to member 'three'.

`(<Foo> two: ({ 2 }) )`
creates an instance of struct Foo which is all empty except for member 'two' which is assigned the value `({ 2 })`.

It is not possible to use both named and unnamed initializers in the same literal.

## USAGE IN CLOSURES #

The `#'(<` operator can be used in lambda closures to create a struct; the type of the struct is given by the 'template' struct passed as first argument. The content of the template struct is irrelevant, so an empty struct suffices. For example, to create an instance of struct Foo:

~~~{.c}
({ #'(<, (<Foo>), 1, ({ 2 }), (<Bar>) })

~~~
The order of the member values is the order in which they appear in the struct definition.

To access a struct member in a lambda closure, use the `#'->` operator with the name of the member as double-quoted symbol or literal string:

~~~{.c}
({ #'->, struct-expression, ''one })
({ #'->, struct-expression, "one" })

~~~

## SYNTAX #

Dunno yet:

struct_definition  ::= "struct " struct_name ["(" struct_name ")"]
                      "{" variable_declaration* "};"
struct_declaration ::= "struct " struct_name ";"
struct_name        ::= identifier
literal            ::= "(<" struct_name ">)"

## MISCELLANEOUS #

Internally structs can be identified by the ID string returned from efun::get_type_info(). This string contains the name of the struct, the name of the program its type was defined in, and the ID number of the program. However, do not rely on a particular format of this string!

Support for structs is signaled by the @ref driver_topics_predefined "__LPC_STRUCTS__".

Though structs are tied to the program the are defined in, re-compiling a program doesn't make the struct types incompatible. Even if the newly compiled struct has a different structure it will be accepted by routines that expect the old struct definition. When members disappeared in the new struct definition, read access to those members will return 0, write access to vanished members however will result in a runtime error.

@usage{
Suppose we have two objects: a monster, and a monster coordinate tracker, and we want to use a struct to store the coordinate:

@par note: Using `#include "monster_coordinate.c"` instead of @ref driver_syntax_inherit "inherit" won't work. While the objects would compile, the first call to `track()` would cause a runtime error similar to: `Illegal type to struct->(): struct Coordinate (/monster.c #234), expected struct Coordinate (/monster_tracker.c #552)`

}

@history{
introduced (3.3.246)
changed (3.3.344) -- implementation revised
changed (3.3.417) -- implemented reactivation of unchanged structs in object updates
}

@see @ref driver_syntax_mappings "mapping", efun::get_type_info(), efun::structp(), efun::mkmapping(), efun::to_struct(), efun::struct_info(), efun::baseof()
