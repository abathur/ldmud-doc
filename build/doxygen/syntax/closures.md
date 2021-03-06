closures {#driver_syntax_closures}
==================================
Closure: `closure`
@par note: This is the official man page concerning closures. If you find it hard to read maybe the Closure Guide is an easier introduction for you: See @ref driver_syntax_closure_guide "closures" and @ref driver_syntax_closures-example "closures example".

Closures provide a means of creating code dynamically and passing pieces of code as parameters, storing them in variables. One might think of them as a very advanced form of efun::process_string(). However, this falls short of what you can actually do with them.

The simplest kind of closures are efuns, lfuns or operators. For example, `#'this_player` is an example of a closure. You can assign it to a variable as in:

~~~{.c}
closure f;
object p;
f = #'this_player;

~~~
and later use either the efun::funcall() or efun::apply() efun to evaluate it. Like:

~~~{.c}
p = funcall(f);

~~~
or:

~~~{.c}
p = apply(f);

~~~
In both cases there p will afterwards hold the value of `this_player()`. Of course, this is only a rather simple application.

Inline closures are a variant of lfun closures, the difference being that the function text is written right where the closure is used. Since they are pretty powerful by themselves, inline closures have their own manpage.

More useful instances of closures can be created using the efun::lambda() efun. It is much like the lambda function in LISP. For example, you can do the following:

~~~{.c}
f = lambda( ({ 'x }), ({ #'environment, 'x }) );

~~~
This will create a lambda closure and assign it to f. The first argument to lambda is an array describing the arguments (symbols) passed to the closure upon evaluation by efun::funcall() or efun::apply(). You can now evaluate f, for example by means of `funcall(f,this_object())`. This will result in the following steps:

1. The value of `this_object()` will be bound to symbol x.
2. `environment(x)` evaluates to `environment(this_object())` and is returned as the result of the efun::funcall().
One might wonder why there are two functions, efun::funcall() and efun::apply(), to perform the seemingly same job, namely evaluating a closure. Of course there is a subtle difference. If the last argument to efun::apply() is an array, then each of its elements gets expanded to an additional paramater. The obvious use would be `#'call_other` as in:

~~~{.c}
mixed eval(object ob,string func,mixed *args) {
  return apply(#'call_other,ob,func,args);
}

~~~
This will result in calling `ob->func(args[0],args[1],...,args[sizeof(args)-1])`. Using efun::funcall() instead of efun::apply() would have given us `ob->func(args)`.

Of course, besides efuns there are closures for >>:concept:`operators`<<, like `#'+`, `#'-`, `#'<`, `#'&&`, etc.

Well, so far closures have been pretty much limited despite their obvious flexibility. This changes now with the introduction of conditional and loop operators. For example, try:

~~~{.c}
closure max;
max = lambda(
  ({ 'x, 'y }),
  ({
    #'?,
    ({ #'>, 'x, 'y }),
    'x,
    'y
  })
);
return funcall(max,7,3);

~~~
The above example will return 7. What happened? Of course `#'?` is the conditional operator and its 'syntax' is as follows:

~~~{.c}
({ #'?, cond1, val1, cond2, val2, ..., condn, valn, valdefault });

~~~
It evaluates cond1, cond2, ..., condn successively until it gets a nonzero result and then returns the corresponding value. If there is no condition evaluating to a nonzero result, valdefault gets returned. If valdefault is omitted, 0 gets returned. `#'?!` works just like `#'?`, except that the `` is applied to conditions before testing. Therefore, while `#'?` is somewhat like an if statement, `#'?!` resembles an if_not statement if there were one.

There are also loops:

~~~{.c}
({ #'do, loopbody1, ..., loopbodyN, loopcond, loopresult })

~~~
will evaluate the loopbodies until loopcond evaluates to 0 and then return the value of loopresult. Symbols may be used as variables, of course.:

~~~{.c}
({ #'while, loopcond, loopresult, loopbody1, ..., loopbodyN })

~~~
works similar but evaluates loopcond before the loopbodies.

The @ref driver_syntax_foreach "foreach" loop also has a closure form:

~~~{.c}
({ #'foreach, 'var, expr, loopbody1, ..., loopbodyN })
({ #'foreach, ({ 'var1, ..., 'varN}) , expr, loopbody1, ..., loopbodyN })

~~~
Now on to a couple of tricky things:

1. How do I write down an array within a lambda closure to avoid interpretation as a subclosure?
`({ #'member, ({ "abc", "xyz" }), 'x })` will result in an error as soon as efun::lambda() tries to interpret "abc" as a closure operator. The solution is to quote the array, as in: `({ #'member, '({ "abc", "xyz" }), 'x })`. Applying efun::lambda() to this will not result in an error. Instead, the quote will be stripped from the array and the result regarded as a normal array literal. The same can be achieved by using efun::quote(), e.g.:

~~~{.c}
({ #'member, quote( ({ "abc", "xyz" }), 'x ) })

~~~

2. Isn't it a security risk to pass, say, a closure to the master object which then evaluates it with all the permissions it got?
Luckily, no. Each closure gets upon compilation bound to the object defining it. That means that executing it first sets `this_object()` to the object that defined it and then evaluates the closure. This also allows us to call lfuns which might otherwise be undefined in the calling object.

There is however, a variant of efun::lambda(), called efun::unbound_lambda(), which works similar but does not allow the use of lfuns and does not bind the closure to the defining object. The drawback is that trying to evaluate it by efun::apply() or efun::funcall() will result in an error. The closure first needs to be bound by calling efun::bind_lambda(). efun::bind_lambda() normally takes one argument and transforms an unbound closure into a closure bound to the object executing the efun::bind_lambda().

Privileged objects, like the master and the simul_efun object (or those authorized by master::privilege_violation()) may also give an object as the second argument to efun::bind_lambda(). This will bind the closure to that object. A sample application is:

~~~{.c}
dump_object(ob)
// will dump the variables of ob to /dump.o
{
  closure save;
  save = unbound_lambda( ({ }), ({ #'save_object, "/open/dump" }) );
  bind_lambda(save,ob);
  funcall(save);
}

~~~
efun::bind_lambda() can also be used with efun closures.

3. It might be an interesting application to create closures dynamically as an alternative to writing LPC code to a file and then loading it. However, how do I avoid doing exactly that if I need symbols like `'x` or `'y`?
To do that one uses efun::quote(). It takes a string as its argument and transforms it into a symbol. For example, writing `quote("x")` is exactly the same as writing `'x`.

4. How do I test if a variable holds a closure?
Use the efun::closurep() efun which works like all the other type testing efuns. For symbols there is also efun::symbolp() available.

5. That means, I can do: `if (closurep(f)) return funcall(f); else return f;` ?
Yes, but in the case of efun::funcall() it is unnecessary. If efun::funcall() gets only one argument and it is not a closure it will be returned unchanged. So return `funcall(f);` would suffice.

6. I want to use a function in some object as a closure. How do I do that?
There are several ways. If the function resides in `this_object()`, just use `#'func_name`. If not, or if you want to create the function dnynamically, use the efun efun::symbol_function(). It takes a string as it first and an object as its second argument and returns a closure which upon evaluation calls the given function in the given object (and faster than efun::call_other(), too, if done from inside a loop, since function search will be done only when calling efun::symbol_function().

7. Can I create efun closures dynamically, too?
Yes, just use efun::symbol_function() with a single argument. Most useful for marker objects and the like. But theoretically a security risk if not used properly and from inside a security relevant object. Take care, however, that, if there is a simul_efun with the same name, it will be preferred as in the case of `#'function`. Use the `efun::` modifier to get the efun if you need it.

8. Are there other uses of closures except using them to store code?
Lots. For example, you can use them within almost all of the efuns where you give a function as an argument, like efun::filter(), efun::sort_array() or efun::walk_mapping(). `sort_array(array,#'>)` does indeed what is expected. Another application is efun::set_prompt(), where a closure can output your own prompt based on the current time and other stuff which changes all the time.

Finally, there are some special efun/operator closures:

`#'[` : indexes an array.
`#'[<` : does the same, but starting at the end.
`#'[..]` : gets an array and two numbers and returns a sub-array.
`#'[..<]` : same as above but the second index is interpreted as counted from the left end.
`#'[<..]`  and
`#'[<..<]` : should be clear now.
`#'[..` : takes only one index and returns the sub- array from this index to the end.
`#'[<..` : same as above but the index is interpreted as counted from the left end.
`#'({` : puts all arguments into an array.
`#'([` : gets an unquoted (!) array which must include at least one element as argument and returns a mapping of the width of the given array's size with one entry that contains the first element as key and the other elements as values to the key.

`#'negate` is for unary minus.
`#'`, may be followed by any number of closures, e.g.: `({ (#',), ({#'= 'h, 'a, }), ({#'=, 'a, 'b }), ({#'=, 'b, 'h }) })` will swap 'a and 'b when compiled and executed.

## closures-abstract #

### Procedural elements #

definition of terms:

`<block>`
zero or more values to be evaluated.

`<test>`
one value to be evaluated as branch or loop condition.

`<result>`
one value to be evaluated at the end of the execution of the form; the value is returned.

`<lvalue>`
local variable/parameter, global variable, or an indexed lvalue.

used EBNF operators:

~~~{.c}
{ }     iteration
[ ]     option

~~~
forms:

- `({#', <body> <result>})`
- `({#'? { <test> <result> } [ <result> ] })`
- `({#'?! { <test> <result> } [ <result> ] })`
- `({#'&& { test } })`
- `({#'|| { test } })`
- `({#'while <test> <result> <body>})`    loop while test evaluates non-zero.
- `({#'do <body> <test> <result>})`       loop till test evaluates zero.
- `({#'= { <lvalue> <value> } })`         assignment other assignment operators work, too.

lisp similars:

~~~{.c}
#',           progn
#'?           cond
#'&&          and
#'||          or
#'while       do      /* but lisp has more syntactic candy here */
#'=           setq

~~~
A parameter / local variable 'foo' is referenced as 'foo , a global variable as `({#'foo})`. In lvalue positions (assignment), you need not enclose global variable closures in arrays.

Call by reference parameters are given with `({#'&, <lvalue>})`

Some special efuns:

~~~{.c}
#'[             indexing
#'[<            indexing from the end
#'negate        unary -

~~~

### Unbound lambda closures #

These closures are not bound to any object. They are created with the efun efun::unbound_lambda(). They cannot contain references to global variables, and all lfun closures are inserted as is, since there is no native object for this closure. You can bind and rebind unbound lambda closures to an object with efun efun::bind_lambda() You need to bind it before it can be called. Ordinary objects can obly bind to themselves, binding to other objects causes a privilege violation. The point is that previous_object for calls done from inside the closure will reflect the object doing efun::bind_lambda(), and all object / uid based security will also refer to this object.

Authors
MacBeth, Amylaar, Hyp

@see @ref driver_syntax_closures-example "closures example", @ref driver_syntax_closure_guide "closures"
