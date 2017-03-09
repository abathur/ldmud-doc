inline-closures {#driver_syntax_inline-closures}
================================================
Inline closures are a way to program closures which are compiled at the time an object is loaded, but can access values from their enclosing function at runtime.

@par note: Inline closures are not to be confused with inline functions known from other languages.

In the definition of an inline closure, some elements are optional:

~~~{.c}
<returntype>     defaults to 'mixed'
( <arguments> )  defaults to '(mixed $1 ...  mixed $9)'
: <context>      no default

~~~
The special `(: :)` form is meant for simple expressions (and MudOS compatibility). The form:

~~~{.c}
(: <statements> ; <expr>, ..., <expr> :)

~~~
is the shorthand notation for:

~~~{.c}
function { <statements>; return <expr>, ..., <expr>; }

~~~
For example the two statements:

~~~{.c}
sort_array(arr, function { return $1 < $2; } )
sort_array(arr, (: $1 < $2 :) )

~~~
do the same. The example also demonstrates that both the `statements` and the `expr` part in this form are optional.

@usage{
The closure below 'inherits' the current value of the local variable 'arg' at the time the closure is created. These values, called the "context" of the closures, are stored in a special set of variables in the closure:

~~~{.c}
closure factory (int arg) {
  return function int (int val) { return val * arg; };
}

closure f1 = factory(2);
closure f2 = factory(3);
funcall(f1, 3); // returns 6.
funcall(f2, 3); // returns 9.

~~~
The closure can permanently change its context:

~~~{.c}
closure factory (int arg) {
  return function int (int val) { return val * arg++; };
}

closure f = factory(2);
funcall(f, 3); // will yield 6.
funcall(f, 3); // will now yield 9!

~~~
@par note: Changes to the closure context will not reflect on the local variable it was copied from or vice versa.

In addition to the implicit context inherited from the defining function, additional context variables can be defined in the closure:

~~~{.c}
closure factory (int arg) {
  return function int (int val) : int x = 2 * arg { return val * x; };
}

closure f = factory(2);
funcall(f, 3) -> will yield 12.

~~~
It is possible to define multiple context variables with and without initialisation:

~~~{.c}
closure factory (int arg) {
  return function int (int val) : int y, x = 2 * arg; int z { return val * x; };
}

~~~
These explicit context variables are useful when the closures needs to keep a state, or to improve performance:

~~~{.c}
mapping m = ...;
closure slow (int arg) {
  return function mixed () { return m[arg]; }
}
closure fast (int arg) {
  return function mixed () : mixed val = m[arg] { return val; }
}

~~~
In the above example, the `fast()` function executes the lookup m[arg] only once when the inline closure is created; the `slow()` function on the other hand returns a closures which looks up `m[arg]` every time it is called. A second effect is that the results of the slow closure change when `m` changes; the result of the fast closure is always the same.

}

@history{
changed (3.2.7) -- implemented the older, restricted form of inline closures.
changed (3.3.271) -- implemented the full form of inline closures.
changed (3.3.275) -- re-allowed statements in the (: :) form.
}

@see @ref driver_syntax_closure_guide "closures", @ref driver_syntax_closures "closure"
