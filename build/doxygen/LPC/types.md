types {#driver_LPC_types}
=========================
Variables can have the following types:

@ref driver_LPC_int "int"
An integer.

@ref driver_LPC_string "string"
A text string.

@ref driver_LPC_status "status"
@par obsolete:status was planned to be an optimized boolean format, but this was never actually implemented. status does work; however, since it is only an alias for type 'int', just use int.

@ref driver_LPC_object "object"
Pointer to an object. Objects are always passed by reference.

@ref driver_LPC_arrays "arrays"
Pointer to a vector of values, which could also be an alist. Arrays take the form ({ n1, n2, n3 }) and may contain any type or a mix of types. Arrays are always passed by reference. Note that the size of arrays in LPC, unlike most programming languages, CAN be changed at run-time.

@ref driver_LPC_mappings "mappings"
An 'associative array' consisting of values indexed by keys. The indices can be any kind of datatype. Mappings take the form ([ key1: value1, key2: value2 ]). By default, mappings are passed by reference.

@ref driver_LPC_closures "closures"
References to executable code, both to local functions, efuns and to functions compiled at run-time ("lambda closures").

@ref driver_LPC_symbol "symbol"
Identifier names, which in essence are quoted strings. They are used to compute lambda closures, e.g. instead of ({..., 'ident, ... }) you can write declare a 'symbol' variable foo, compute a value for it, and then create the closure as ({ ..., foo, ... })

@ref driver_LPC_float "float"
A floating-point number.

@ref driver_LPC_mixed "mixed"
A variable allowed to take a value of any type (int, string, object, array, mapping, float or closure).

@ref driver_LPC_structs "struct"
A collection of values. See @ref driver_LPC_structs "struct".

@ref driver_LPC_unions "unions"
A range of types, either of which the variable can contain at runtime. See `unions`.

All uninitialized variables have the value 0.

The type of a variable is really only for documentation. Unless you define #pragma strong_types or rtt_checks, variables can actually be of any type and has no effect at all on the program. However, it's extremely bad style to declare one type but use another, so please try to avoid this.

@see @ref driver_LPC_arrays "arrays", @ref driver_LPC_mappings "mappings", @ref driver_LPC_closures "closures", @ref driver_LPC_structs "struct", @ref driver_LPC_unions "unions", efun::typeof(), efun::get_type_info(), @ref driver_concepts_inheritance "inheritance", @ref driver_LPC_pragma "pragma", @ref driver_LPC_modifiers "modifiers", @ref driver_LPC_escape "escape"
