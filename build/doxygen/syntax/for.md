for {#driver_syntax_for}
========================
Execute `init` once. Then, while `expr2` returns a non-zero value, execute `statement`. Every time `statement` has been executed, or a `continue` statement has been executed, execute `expr3` before next loop.

`init` is usually a series of one or more expressions (remember that assignments are expressions, too), separated by commas. Additionally it is also allowed to define new local variables here and assign them an initial value. The scope of such variables is the whole for statement.

@usage{
Examples for legal `init` expressions are:

~~~{.c}
for (i = 0; ...
for (i = 0, j = 0; ...
for (i = 0, int j = i; ...
for (int j = 4; ...

~~~
Illegal `init` expressions are:

~~~{.c}
for (int i; ...      // no value assigned
for (int i += 4; ... // only plain assignments allowed

~~~
A `break` in the `statement` will terminate the loop. A `continue` will continue the execution from the beginning of the loop.

}

@see @ref driver_syntax_foreach "foreach", @ref driver_syntax_if "if", @ref driver_syntax_do-while "do-while", @ref driver_syntax_while "while", @ref driver_syntax_switch "switch"
