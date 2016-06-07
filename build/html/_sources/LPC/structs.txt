.. type:: struct
  :synopsis: structs are, next to arrays and mappings, a way to group a
    collection of values together.

    .. .. productionlist:: struct_usage
      declare: struct struct_name;
      define: struct name (parent) {int one;};
      construct: (<struct_name>)
        : (<struct_name> 1)
        : (<`struct_name`> one: 1)
        : test (* comment *) test
      struct_name: beeps

  A struct holds a fixed number of values, called 'members', and allows to access them by their given name. The name is resolved when the LPC code is compiled, making struct member access as fast as array member access.

  Structs are passed by reference.

  .. subtopic:: DEFINING

    A new struct type has to be :token:`defined <struct_definition>` at the top level of an object. For example::

      struct Foo {
        int        one, *two;
        struct Bar three;
      };

    defines the new struct 'Foo' with three members: integer 'one', integer array 'two', and struct Bar 'three'

    It is possible to 'inherit' structs from each other. Given above definition of struct Foo, the following definition ::

      struct Quux (Foo) {
        int four;
      };

    is equivalent to the definition::

      struct Quux {
        int        one, *two;
        struct Bar three;
        int four;
      };

    The usual visibility modifiers apply, e.g. ::

      protected struct Bang {...};

    struct definitions are promoted through inheritance like functions, with the difference that all structs live in the same flat namespace. This means: a struct defined in a program is visible in _all_ inherited programs, regardless of how deep the inheritance is nested. This also means that in one program there must not be two structs, inherited or not, with the same name.

    To :token:`declare <struct_declaration>` a struct without defining it, write::

      struct Quux;

    This notation is useful if you have two structs referencing each other::

      struct Quux;

      struct Bar {
        struct Quux quux;
      };
      struct Quux {
        struct Bar bar;
      };

  .. subtopic:: CREATING

    To use a struct, its definition must be visible - either because it is defined in the object compiled, or it has been inherited.

    .. note:: #include'ing structs does not what you think it does: in LPC it constructs a new struct type whereever it is included.

    A variable to hold a struct is defined like this::

      struct Foo var;

    and similar for function arguments::

      void fun (struct Foo arg)

    Just writing 'struct Foo var' however does not _create_ a struct, it just creates a variable capable of holding one. To assign a value to the variable upon creation, assign it with a struct value, either from another variable or from a literal struct::

      struct Foo var = (<Foo>);

    Literal structs are written using (<>) as delimiters:

    ``(<Foo>)``
      creates an empty instance of struct Foo

    ``(<Foo> 1, ({ 2 }), bar)``
      creates an instance of struct Foo, and assigns 1 to member 'one', ({ 2 }) to member 'two', and the content of variable bar to member 'three'.

    ``(<Foo> two: ({ 2 }) )``
      creates an instance of struct Foo which is all empty except for member 'two' which is assigned the value ({ 2 }).

    It is not possible to use both named and unnamed initializers in the same literal.

  .. usage::

    A struct member is accessed using the -> operator::

      struct Foo var = ...;

      var->one = 1;

    It is possible to compute struct lookups at runtime::

      struct Foo bar = ...;
      string member = "one";

      bar->(member) = 1; // sets bar->one to 1
      bar->(0) = 1;      // sets bar->one to 1

    When using struct values held in variables/expressions of type 'mixed', the 'mixed' value should to be casted to the struct value. The cast can be omitted if the looked-up member exists in only one struct (and its children) known to the compiler::

      struct Foo { int one; };
      struct Bar { int two; };
      struct Baz { int two; };
      mixed var;

      var->one              // looks up Foo->one
      (struct Foo)var->one  // looks up Foo->one
      var->two              // ERROR: ambiguous lookup
      (struct Bar)var->one  // looks up Bar->one

  .. subtopic:: USAGE IN CLOSURES

    The #'(< operator can be used in lambda closures to create a struct; the type of the struct is given by the 'template' struct passed as first argument. The content of the template struct is irrelevant, so an empty struct suffices. For example, to create an instance of struct Foo::

      ({ #'(<, (<Foo>), 1, ({ 2 }), (<Bar>) })

    The order of the member values is the order in which they appear in the struct definition.

    To access a struct member in a lambda closure, use the #'-> operator with the name of the member as double-quoted symbol or literal string::

      ({ #'->, struct-expression, ''one })
      ({ #'->, struct-expression, "one" })

  .. subtopic:: SYNTAX

    Dunno yet:

    .. productionlist::
      struct_definition: "struct " `struct_name` ["(" `struct_name` ")"]
        : "{" `variable_declaration`* "};"
      struct_declaration: "struct " `struct_name` ";"
      struct_name: `identifier`
      literal: "(<" `struct_name` ">)"

  .. subtopic:: MISCELLANEOUS

    Internally structs can be identified by the ID string returned from get_type_info(). This string contains the name of the struct, the name of the program its type was defined in, and the ID number of the program. However, do not rely on a particular format of this string!

    Support for structs is signaled by the macro __LPC_STRUCTS__.

    Though structs are tied to the program the are defined in, re-compiling a program doesn't make the struct types incompatible. Even if the newly compiled struct has a different structure it will be accepted by routines that expect the old struct definition. When members disappeared in the new struct definition, read access to those members will return 0, write access to vanished members however will result in a runtime error.

  .. subtopic:: EXAMPLES

    Suppose we have two objects: a monster, and a monster coordinate tracker, and we want to use a struct to store the coordinate:

    .. code-block: c
      :caption: monster_coordinate.c

      struct Coordinate { int x; int y; };

    .. code-block: c
      :caption: monster_tracker.c

      inherit "monster_coordinate";

      void track (struct Coordinate coord) { ... }

    .. code-block: c
      :caption: monster.c

      inherit "monster_coordinate";

      int move (..) {
        ...
        "monster_tracker"->track( (<Coordinate> my_x, my_y) );
      }

    Note that using ``#include "monster_coordinate.c"`` instead of :lang:`inherit` won't work. While the objects would compile, the first call to ``track()`` would cause a runtime error of the type::

      Illegal type to struct->(): struct Coordinate (/monster.c #234), expected struct Coordinate (/monster_tracker.c #552)

  :history 3.3.246 introduced:
  :history 3.3.344 changed: implementation revised
  :history 3.3.417 changed: implemented reactivation of unchanged structs in object updates

  .. seealso:: :lang:`mappings`, :efun:`get_type_info`, :efun:`structp`, :efun:`to_mapping`, :efun:`to_struct`, :efun:`struct_info`, :efun:`baseof`
