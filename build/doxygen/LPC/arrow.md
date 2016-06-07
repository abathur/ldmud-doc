arrow {#driver_LPC_arrow}
=========================
The arrow operator is equivalent to efun::call_other(). This syntax document discusses how the arrow operator relates to the efun version and gives basic examples; you should see efun::call_other() for thorough documentation.

`ob->fun(args)` and `ob->"fun"(args)` are equivalent to `call_other(ob, "fun", args)`. `ob->(fun)(args)` is equivalent to `call_other(ob, fun, args)` where fun is a runtime expression returning the function name.

@usage{
All of the following statements call the lfun QueryProp() in the current player object with a single argument, P_SHORT. First let's do some setup:
string str, fun;
fun = "QueryProp";
Now we'll use these variables with the basic call_other():
str = (string)call_other(this_player(), "QueryProp", P_SHORT);
str = (string)call_other(this_player(), fun, P_SHORT);
And here are three equivalent calls using the arrow syntax form (with the variables from above):
str = (string)this_player()->QueryProp(P_SHORT);
str = (string)this_player()->"QueryProp"(P_SHORT);

str = (string)this_player()->(fun)(P_SHORT);
You can also use the arrow form to call a function on each object in an array. The following statement calls the lfun short() in all interactive users and stores the result in an array of strings:
string *s;
s = (string *)users()->short();
}

@history{
changed (3.2.8) -- the forms x->"y"() and x->(y)() are now recognized;

the form x->y() no longer clashes with a local variable also called "y";

a simul_efun call_other() also catches ->() calls.
the forms x->"y"() and x->(y)() are now recognized;
the form x->y() no longer clashes with a local variable also called "y";
a simul_efun call_other() also catches ->() calls.
changed (3.5.0) -- split documentation for the arrow "->" syntax from documentation for call_other()
}

@see efun::call_other(), efun::call_direct(), efun::call_direct_resolved(), efun::call_resolved(), applied::create(), @ref driver_LPC_pragma "pragma", efun::extern_call(), efun::function_exists(), @ref driver_LPC_functions "functions", efun::map_objects()
