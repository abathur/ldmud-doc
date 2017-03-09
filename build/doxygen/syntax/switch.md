switch {#driver_syntax_switch}
==============================
Branch to the case label in statement that matches expr. If no matching case label is found (by value or by type), branch to the default label in statement.

Keyword: `case`
`case expr [.. expr2]: block`

A case label has the form

~~~{.c}
case expr_n :

~~~
where expr_n must be constant, or the form

~~~{.c}
case expr_n1 .. expr_n2 :

~~~
where expr_n1 and expr_n2 must be numeric constants and expr_n1 < expr_n2.

Either all case labels have to be strings or all have to be numeric. Only 0 is special: it is allowed in a switch statement where all other labels are strings.

Keyword: `default`
`default: block`

A default label has the form

~~~{.c}
default :

~~~
The default label defaults to the end of statement if not given explicitly.

Whenever a 'break' statement is executed inside 'statement' a branch to the end of the switch statement is performed.

@par note: In C, the grammar for switch is:~~~{.c}
switch (expr) statement

~~~allowing constructs like:~~~{.c}
switch (expr)
  while (expr2)
  {
  case 1: ...
  case 2: ...
  }

~~~In LPC a switch must be followed by a block that contains the case labels directly. In contrast to C, the group of statements following a case label have their own lexical scope so that variable declarations may not cross case labels.

@usage{
~~~{.c}
switch(random(100)) {
  case 0 .. 22 : write("Nothing happens"); break;
  case 23 .. 27 :
    write("You are surrounded by a golden glow");
    this_player()->heal_self(random(3));
    break;
  case 28 .. 32 :
    write("The water was poisoned!\n");
    this_player()->add_exp(this_player()->hit_player(random(4)));
    break;
  case 33 : write("You hear a voice whispering: "+random_hint());
  /* fall through */
  case 34 :
    write(
      "While you didn't pay attention, a water demon "
      "snatches a coin out of your purse!\n"
    );
    this_player()->add_money(-1);
    break;
  default : write "You hear some strange noises\n"; break;
  case 42 : return;
  case 99 : write("It tastes good.\n";
}

~~~

}

@history{
changed (3.2.10) -- constrained the grammar to require a block for the switch() body, not just a statement. This differs from the C syntax, but was necessary as the compiler didn't handle the statement case correctly.
changed (3.3) -- allowed to pass values of the wrong type to switch(), the driver would in that case use the default case. Before, values of the wrong type caused a runtime error.
changed (3.3.718) -- disallowed case labels in inner blocks and variable declarations that cross case labels.
}

@see @ref driver_syntax_for "for", @ref driver_syntax_foreach "foreach", @ref driver_syntax_do-while "do-while", @ref driver_syntax_if "if", @ref driver_syntax_while "while"
