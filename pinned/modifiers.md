modifiers {#driver_syntax_modifiers}
====================================
A modifier changes the syntactic and/or semantic behaviour of an object-global variable or a function in an object. The existing modifiers are described below. To use a modifier just prepend it to the declaration. If several modifiers are to be used their order does not matter:

~~~{.c}
private int bar;                         // example for a variable
protected nomask int foo() { return 3; } // example for a function

~~~
## For functions #

private
such functions can only be called with an internal call from within this file. Not even inheriting objects can call these functions. You can nevertheless build an lfun-closure with `#'` out of a private function (but you cannot save and restore it).

protected
such functions can be called from within the object, or from inheriting objects; but in neither case with efun::call_other(). It is possible to create `#'` closures or use efun::symbol_function() from within the object. Its use is preferred over the older "static".

static
such functions can be called from within the object in either way (internal call or with efun::call_other()). Inheriting objects can call such functions. But it is not possible to call static functions from other objects via efun::call_other(). The use of 'static' in new code is not recommended. Note that an efun::add_action() is treated like a call from within the object except the player who got the efun::add_action() was forced (thus it is a simple way to secure an efun::add_action() against forces, although this method has the severe disadvantages of raising an error at the force so better use the security system). Also efuns like efun::call_out() or efun::input_to() can call these functions if given as a string.

public
this is the default type. Such functions can be called from within the file as well as from inheriting objects and other objects via efun::call_other(). To declare a function public only results in the impossibility to change the accessibility at the inherit statement (see below). No error will occur, only the type will not be modified by the inherit statement.

nomask
such functions cannot be overridden by inheriting objects. If you have the fun `foo()` defined in your object and inherit an object which also has declared a function `foo()` and this nomask, you will get an compile error if you try to load your object. Furthermore a shadow will fail if it tries to shadow a nomask declared function.

varargs
this changes the syntax of the function in a way that not all of the arguments in the declaration must be given at the call. This is often very usefull if some of the arguments shall be omitable (the omitted arguments are set to 0 if the function is called with fewer arguments than specified). This is mainly within the object really necessary; :efun:>>`<<call_other`s usually (that is if they do not have a certain pragma ('man pragma')) do not need the called function to be declared varargs to omit any arguments, but it is good style to use this modifier to document the code by this.

deprecated
Whenever this function is called, a warning is issued. Usually this is done at compile-time. Exceptions are call_others and efun::symbol_function() which warn at run-time.

## For object-global variables #

private
such variables can only be accessed from within the same object. Not even inheriting objects can access private variables. It is a good style to declare all internal variables private to prevent inheriting objects from accessing the variables directly without using functions.

nosave
such variables are neither stored with efun::save_object() nor restored with efun::restore_object(). This can be very useful if you want a room to use efun::save_object() and efun::restore_object() to save your own defined variables but not the hundreds of variables inherited from a room-class (e.g. /complex/room). You then use the modifier at the inherit statement (see below). Note that nosave and private do not overlap in any way. They are absolutely independant.

static
the old name for 'nosave'. Its use is deprecated.

public
declares the variable public. It cannot be declared private or static by inheriting. No error will occur, only the type will not be modified by the inherit statement.

deprecated
Whenever this variable is used, a warning is issue. Usually this is done at compile-time, but efun::symbol_variable() warns at run-time.

It is no good style to let inheriting objects have access to internal variables so declare them as private and offer functions to query and change the variables if possible.

It is also possible to redeclare all variables and/or functions of an inherited object for the own object at the inheriting statement:

~~~{.c}
private functions nosave variables inherit "complex/room";
public variables inherit "complex/room";
private functions inherit "complex/room";

~~~
To redeclare a function or a variable declared public in the inherited object to be private or protected is not possible.

There also exists a modifier explicitly for the inherit statement:

virtual
inherits the given object virtually. This only makes sense in a complex inherit tree. If an object is inherited normally (not virtually) twice somewhere in the inherit tree the intern variables exist twice. If inherited virtually they exist only once.

Example:

~~~{.c}
A inherits B and C.
B inherits D.
C inherits D.
If the inheritance of D is virtual in B and C
D's variables exist only once in A. If A changes
D's variables via functions of B this also changes
the variables of D as known by C.

 virtual:               non-virtual:
    A                        A
   / \                      / \
  B   C                    B   C
   \ /                     |   |
    D                      D   D

~~~

To simplify the adoption of existing code, LPC allows to specify a default visibility for functions and variables, using a syntax similar to the inherit syntax.

All variables and functions are by default private:

~~~{.c}
default private;

~~~
All variables are by default private, but functions are public:

~~~{.c}
default private variables public functions;

~~~
Only the modifiers `private`, `public` and `protected` (and `static` for functions only) are allowed here.

The default visibility thus set affects only variables/functions with no explicite visibility:

~~~{.c}
default private;

int private_var;
public int public_var;

~~~
The definition is valid from the point of the 'default' statement until the end of the file, or until the next 'default' statement:

~~~{.c}
default private;

int private_var;

default public;

int public_var;

~~~
@par note: this default visibility does not affect inherits.

@history{
changed (3.2.8) -- modifier 'static' for variables was renamed to 'nosave'; 'static' is still recognized as an alias
changed (3.2.9) -- default visibility was added as experimental feature
}

@see @ref driver_syntax_closures "closure", @ref driver_topics_inheritance "inheritance", @ref driver_syntax_functions "functions", @ref driver_syntax_types "types"
