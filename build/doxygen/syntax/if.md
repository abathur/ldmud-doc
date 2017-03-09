if {#driver_syntax_if}
======================
Implements conditional execution of statements. The expressions 'expr1' .. 'exprN' are evaluate in the order they appear until one of the expressions returns non-0 ('true'). At that point, the statement associated with the expression is executed, and the program continues after the @ref driver_syntax_if "if" statement. If none of the expressions evaluate to 'true', the statementX in the 'else'-branch is executed.

Both the 'else if' branches and the 'else' branch are optional, and there can be any number of 'else if' branches - but there must be one 'if' branch, and the branches must be in the order given above.

Any 'else' or 'else if' always relates to the immediately preceeding 'if' resp. 'else if' conditional. This means that:

~~~{.c}
if (a)
if (b) do_b;
else do_c;

~~~
is interpreted as:

~~~{.c}
if (a) {
  if (b) do_b;
  else   do_c;
}

~~~

@see @ref driver_syntax_for "for", @ref driver_syntax_foreach "foreach", @ref driver_syntax_do-while "do-while", @ref driver_syntax_while "while", @ref driver_syntax_switch "switch"
