operators {#driver_syntax_operators}
====================================
These are the operators availailable in LPC. They are listed in the order of precedence (low priority first):

Comma operator: `,`
`expr1 , expr2`

Evaluate 'expr1' and then 'expr2'. The returned value is the result of 'expr2'. The returned value of 'expr1' is thrown away.

Equality operator: `=`
`var = expr`

Evaluate 'expr', and assign the value to 'var'. The new value of 'var' is the result.

Assignment operator: `=`
`var = expr`

Evaluate 'expr', and assign the value to 'var'. The new value of 'var' is the result.

Operator: `+=`
`var += expr`

Shorthand for `var = var + expr`.

Operator: `-=`
`var -= expr`

Shorthand for `var = var - expr`.

Operator: `&=`
`var &= expr`

Shorthand for `var = var & expr`.

Operator: `|=`
`var |= expr`

Shorthand for `var = var | expr`.

Operator: `^=`
`var ^= expr`

Shorthand for `var = var ^ expr`.

Operator: `<<=`
`var <<= expr`

Shorthand for `var = var << expr`.

Operator: `>>=`
`var >>= expr`

Shorthand for `var = var >> expr`.

Operator: `>>>=`
`var >>>= expr`

Shorthand for `var = var >>> expr`.

Operator: `*=`
`var *= expr`

Shorthand for `var = var * expr`.

Operator: `%=`
`var %= expr`

Shorthand for `var = var % expr`.

Operator: `/=`
`var /= expr`

Shorthand for `var = var / expr`.

Operator: `&&=`
`var &&= expr`

Shorthand for `var = var && expr`.

Operator: `||=`
`var ||= expr`

Shorthand for `var = var || expr`.

Ternary operator: `?`
`expr1 ? expr2 : expr3`

Evaluates 'expr1' and branches according to its truth value. If it is true, the 'expr2' is evaluated and returned as result, else 'expr3'.

Operator: `||`
`expr1 || expr2`

The result is true if 'expr1' or 'expr2' is true. 'expr2' is not evaluated if 'expr1' was true.

Operator: `&&`
`expr1 && expr2`

The result is true i 'expr1' and 'expr2' is true. 'expr2' is not evaluated if 'expr1' was false.

Operator: `|`
`expr1 | expr2`

The result is the bitwise or of 'expr1' and 'expr2'.

For arrays, the union set is computed: all elements from `expr1` plus all those from `expr2` which are not in `expr1`.

Operator: `^`
`expr1 ^ expr2`

The result is the bitwise xor of 'expr1' and 'expr2'.

For arrays, the symmetric difference is computed: all elements from `expr1` which are not in `expr2`, plus all those from `expr2` which are not in `expr1`.

Operator: `&`
`expr1 & expr2`

The result is the bitwise and of 'expr1' and 'expr2'.

For arrays and strings, the intersection set (all elements resp. characters from expr1 which which are also in the expr2) is computed.

@par warning: `"aab" & "a" -> "aa"` but `({ 'a','a','b' }) & ({ 'a' }) -> ({ 'a' })`Eventually the array behaviour will be changed to match the string behaviour, so you shouldn't rely on the array behavior in the interim.

Intersecting an array with a mapping is equivalent to intersecting the array with the indices of the mapping: `array & mapping == array & m_indices(mapping)`.

Mappings can be intersected with another mapping or an array. The resulting mapping holds all those entries from the first mapping, which are also mentioned in the second mapping (as index) resp. in the array.

Operator: `==`
`expr1 == expr2`

Compare values. Valid for strings, numbers, objects and closures.

Operator: `!=`
`expr1 != expr1`

Compare values. Valid for strings, numbers, objects and closures.

Operator: `>`
`expr1 > expr2`

Valid for strings and numbers.

Operator: `>=`
`expr1 >= expr2`

Valid for strings and numbers.

Operator: `<`
`expr1 < expr2`

Valid for strings and numbers.

Operator: `<=`
`expr1 <= expr2`

Valid for strings and numbers.

Operator: `<<`
`expr1 << expr2`

Shift 'expr1' left by 'expr2' bits; the sign bit is not preserved.

Operator: `>>`
`expr1 >> expr2`

Shift 'expr1' right by 'expr2' bits. This shift preserves the sign of 'expr1'.

Operator: `>>>`
`expr1 >>> expr2`

Shift 'expr1' right by 'expr2' bits. This shift does not preserve the sign of 'expr1', instead it shifts in 0 bits.

Operator: `+`
`expr1 + expr2`

Add 'expr1' and 'expr2'. If numbers, then arithmetic addition is used. If one of the expressions are a string, then that string is concatenated with the other value. If the expressions are arrays, the result is the right array appended to the left. If the expressions are mappings of equal width, the result is merger of the two mappings. If one key exists in both mappings, the element from the right mapping appears in the result. If the two mappings are of different width, the result is `expr1` if non-empty, and `expr2` otherwise.

Operator: `-`
`expr1 - expr2`

Subtract 'expr2' from 'expr1'. Valid for numbers, strings, arrays, mappings. For arrays and strings, all occurences of the elements resp. characters in 'expr2' are removed from 'expr1', and the result is returned. For mapping, all occurances of elemens in 'expr1' which have a matching key in 'expr2' are removed, and the result is returned.

Operator: `\*`
`expr1 \* expr2`

Multiply 'expr1' with 'expr2'. If strings or arrays are multiplied with a number (zero or positive), the result is a repetition of the original string or array.

Operator: `%`
`expr1 % expr2`

The modulo operator of numeric arguments.

Operator: `/`
`expr1 / expr2`

Integer division.

Operator: `++`
`++ var`

Increment the value of variable 'var', and return the new value.

Operator: `--`
`-- var`

Decrement the value of variable 'var', and return the new value.

Operator: `-`
`- var`

Compute the negative value of 'var'.

Operator: `!`
`! var`

Compute the logical 'not' of an integer.

Operator: `~`
`~ var`

The boolean 'not' of an integer.

Casting operator: `( type ) var`
Return the value of `var` converted to `type`. `type` can be 'string', 'int', 'object', 'float' or 'int*'. `var` must be of a specific type for a conversion to take place; if `var` is 'mixed' or unknown, the cast is purely declarative. Also, if the declared type of `var` is that of `type`, the value is not changed.

   NB. The literal number 0 is of unknown type, as it doubles as 'not initialized' for strings, objects, and arrays.
   
   The operator acts like efun::to_string(), efun::to_int(), efun::to_object(), efun::to_float() and efun::to_array(). It is advisable to use the efuns directly instead of the cast.
   
Operator: `({ type }) var`
`var` is now assumed to have the type `type`. This is purely declarative, the actual value of `var` is not changed.

Operator: `++`
`var ++`

Increment the value of variable 'var', and return the old value.

Operator: `--`
`var --`

Decrement the value of variable 'var', and return the old value.

Operator: `expr1[expr2]`
The array or mapping given by 'expr1' is indexed by 'expr2'.

Operator: `expr1[expr2..expr3]`
Extracts a piece from an array or string. expr2 or expr3 may be omitted, default is the begin or end of expr1. Negative numbers for expr2 or expr3 mean `count from before the beginning`, i.e. foo[-2..-1] is an empty array or string. foo[<2..<1] gives the 2nd and last element of the array resp. chars of the string.

Operator: `expr1->name(...)`
The symbolic form of efun::call_other(). 'expr1' gives either an object or a string which is used as the file_name of an object, and calls the function 'name' in this object.

Operator: `ident::name(...)`
Call the inherited function 'name' with the given parameters in the parent 'ident'. 'ident' may be given as string containing the full pathname, or as identifier containing the pure basename. If 'ident' is omitted, the last inherited function of this 'name' is called.

Operator: `({ })`
Array constructor.

Operator: `([ ])`
Mapping constructor.

@par note: The closure operators are not described here.

operators ::= arrow_operator | arithmetic_operators

@history{
changed (3.2.9) -- added >>>, >>>=, &&= and ||=.
changed (3.2.10) -- extended & to mappings.
changed (3.3) -- extended | and ^ to arrays.
}

@see @ref driver_syntax_arrays "array", @ref driver_syntax_mappings "mapping", @ref driver_syntax_closures "closure"
