.. lang:: operators

  These are the operators availailable in LPC. They are listed in the order of precedence (low priority first):

  .. todo:: probably want to document all of these with a ``.. operator::`` directive, can probably also pull some of the less-operator things out of here and lean on the syntax index and quickref

  .. operator:: ,
    expr1 , expr2
    :name: comma

    Evaluate 'expr1' and then 'expr2'. The returned value is the result of 'expr2'. The returned value of 'expr1' is thrown away.

  .. operator:: =
    var = expr
    :name: equality

    Evaluate 'expr', and assign the value to 'var'. The new value of 'var' is the result.

  .. operator:: =
    var = expr
    :name: Assignment

    Evaluate 'expr', and assign the value to 'var'. The new value of 'var' is the result.

  .. operator:: +=
    var += expr

    Shorthand for ``var = var + expr``.

  .. operator:: -=
    var -= expr

    Shorthand for ``var = var - expr``.

  .. operator:: &=
    var &= expr

    Shorthand for ``var = var & expr``.

  .. operator:: |=
    var |= expr

    Shorthand for ``var = var | expr``.

  .. operator:: ^=
    var ^= expr

    Shorthand for ``var = var ^ expr``.

  .. operator:: <<=
    var <<= expr

    Shorthand for ``var = var << expr``.

  .. operator:: >>=
    var >>= expr

    Shorthand for ``var = var >> expr``.

  .. operator:: >>>=
    var >>>= expr

    Shorthand for ``var = var >>> expr``.

  .. operator:: *=
    var *= expr

    Shorthand for ``var = var * expr``.

  .. operator:: %=
    var %= expr

    Shorthand for ``var = var % expr``.

  .. operator:: /=
    var /= expr

    Shorthand for ``var = var / expr``.

  .. operator:: &&=
    var &&= expr

    Shorthand for ``var = var && expr``.

  .. operator:: ||=
    var ||= expr

    Shorthand for ``var = var || expr``.

  .. operator:: ?
      : expr1 ? expr2 : expr3
    :name: ternary
    :highlighters: \?
      \:

    Evaluates 'expr1' and branches according to its truth value. If it is true, the 'expr2' is evaluated and returned as result, else 'expr3'.

  .. operator:: ||
    expr1 || expr2

    The result is true if 'expr1' or 'expr2' is true. 'expr2' is not evaluated if 'expr1' was true.

  .. operator:: &&
    expr1 && expr2

    The result is true i 'expr1' and 'expr2' is true. 'expr2' is not evaluated if 'expr1' was false.

  .. operator:: |
    expr1 | expr2

    The result is the bitwise or of 'expr1' and 'expr2'.

    For arrays, the union set is computed: all elements from :part:`expr1` plus all those from :part:`expr2` which are not in :part:`expr1`.

  .. operator:: ^
    expr1 ^ expr2

    The result is the bitwise xor of 'expr1' and 'expr2'.

    For arrays, the symmetric difference is computed: all elements from :part:`expr1` which are not in :part:`expr2`, plus all those from :part:`expr2` which are not in :part:`expr1`.

  .. operator:: &
    expr1 & expr2

    The result is the bitwise and of 'expr1' and 'expr2'.

    For arrays and strings, the intersection set (all elements resp. characters from expr1 which which are also in the expr2) is computed.

    .. warning:: ``"aab" & "a" -> "aa"`` but ``({ 'a','a','b' }) & ({ 'a' }) -> ({ 'a' })``

      Eventually the array behaviour will be changed to match the string behaviour, so you shouldn't rely on the array behavior in the interim.

    Intersecting an array with a mapping is equivalent to intersecting the array with the indices of the mapping: ``array & mapping == array & m_indices(mapping)``.

    Mappings can be intersected with another mapping or an array. The resulting mapping holds all those entries from the first mapping, which are also mentioned in the second mapping (as index) resp. in the array.

  .. operator:: ==
    expr1 == expr2

    Compare values. Valid for strings, numbers, objects and closures.

  .. operator:: !=
    expr1 != expr1

    Compare values. Valid for strings, numbers, objects and closures.

  .. operator:: >
    expr1 > expr2

    Valid for strings and numbers.

  .. operator:: >=
    expr1 >= expr2

    Valid for strings and numbers.

  .. operator:: <
    expr1 < expr2

    Valid for strings and numbers.

  .. operator:: <=
    expr1 <= expr2

    Valid for strings and numbers.

  .. operator:: <<
    expr1 << expr2

    Shift 'expr1' left by 'expr2' bits; the sign bit is not preserved.

  .. operator:: >>
    expr1 >> expr2

    Shift 'expr1' right by 'expr2' bits. This shift preserves the sign of 'expr1'.

  .. operator:: >>>
    expr1 >>> expr2

    Shift 'expr1' right by 'expr2' bits. This shift does not preserve the sign of 'expr1', instead it shifts in 0 bits.

  .. operator:: +
    expr1 + expr2

    Add 'expr1' and 'expr2'. If numbers, then arithmetic addition is used. If one of the expressions are a string, then that string is concatenated with the other value. If the expressions are arrays, the result is the right array appended to the left. If the expressions are mappings of equal width, the result is merger of the two mappings. If one key exists in both mappings, the element from the right mapping appears in the result. If the two mappings are of different width, the result is :part:`expr1` if non-empty, and :part:`expr2` otherwise.

  .. operator:: -
    expr1 - expr2

    Subtract 'expr2' from 'expr1'. Valid for numbers, strings, arrays, mappings. For arrays and strings, all occurences of the elements resp. characters in 'expr2' are removed from 'expr1', and the result is returned. For mapping, all occurances of elemens in 'expr1' which have a matching key in 'expr2' are removed, and the result is returned.

  .. operator:: \*
    expr1 \* expr2

    Multiply 'expr1' with 'expr2'. If strings or arrays are multiplied with a number (zero or positive), the result is a repetition of the original string or array.

  .. operator:: %
    expr1 % expr2

    The modulo operator of numeric arguments.

  .. operator:: /
    expr1 / expr2

    Integer division.

  .. operator:: ++
    ++ var

    Increment the value of variable 'var', and return the new value.

  .. operator:: --
    -- var

    Decrement the value of variable 'var', and return the new value.

  .. operator:: -
    - var

    Compute the negative value of 'var'.

  .. operator:: !
    ! var

    Compute the logical 'not' of an integer.

  .. operator:: ~
    ~ var

    The boolean 'not' of an integer.

  .. operator:: ( type ) var
    :name: casting

    Return the value of :part:`var` converted to :part:`type`. :part:`type` can be 'string', 'int', 'object', 'float' or 'int*'. :part:`var` must be of a specific type for a conversion to take place; if :part:`var` is 'mixed' or unknown, the cast is purely declarative. Also, if the declared type of :part:`var` is that of :part:`type`, the value is not changed.

      NB. The literal number 0 is of unknown type, as it doubles as 'not initialized' for strings, objects, and arrays.

      The operator acts like :efun:`to_string`, :efun:`to_int`, :efun:`to_object`, :efun:`to_float` and :efun:`to_array`. It is advisable to use the efuns directly instead of the cast.

  .. operator:: ({ type }) var

    :part:`var` is now assumed to have the type :part:`type`. This is purely declarative, the actual value of :part:`var` is not changed.

    .. todo:: should probably include an example of why this is useful.

  .. todo:: entertain combining the before/after forms and just explain the difference

  .. operator:: ++
    var ++

    Increment the value of variable 'var', and return the old value.

  .. operator:: --
    var --

    Decrement the value of variable 'var', and return the old value.

  .. todo:: next few operators are documented in other files, should those reference this list? should this reference those lists? Should this be a generated list combined from many defs stored elsewhere?

  .. operator:: expr1[expr2]

    The array or mapping given by 'expr1' is indexed by 'expr2'.

  .. operator:: expr1[expr2..expr3]

    Extracts a piece from an array or string. expr2 or expr3 may be omitted, default is the begin or end of expr1. Negative numbers for expr2 or expr3 mean ``count from before the beginning``, i.e. foo[-2..-1] is an empty array or string. foo[<2..<1] gives the 2nd and last element of the array resp. chars of the string.

  .. operator:: expr1->name(...)

    The symbolic form of :efun:`call_other`. 'expr1' gives either an object or a string which is used as the file_name of an object, and calls the function 'name' in this object.

  .. operator:: ident::name(...)

    Call the inherited function 'name' with the given parameters in the parent 'ident'. 'ident' may be given as string containing the full pathname, or as identifier containing the pure basename. If 'ident' is omitted, the last inherited function of this 'name' is called.

  .. todo:: constructors should probably be documented elsewhere.

  .. operator:: ({ })

    Array constructor.

  .. operator:: ([ ])

    Mapping constructor.

  .. note:: The closure operators are not described here.

  .. todo:: above should link to closure operators, but not sure what the directive/roles should be yet

  .. productionlist::
    operators: `arrow_operator` | `arithmetic_operators`

  :history 3.2.9 changed: added ``>>>``, ``>>>=``, ``&&=`` and ``||=``.
  :history 3.2.10 changed: extended ``&`` to mappings.
  :history 3.3 changed: extended ``|`` and ``^`` to arrays.

  .. seealso:: :type:`array`, :type:`mapping`, :type:`closure`
