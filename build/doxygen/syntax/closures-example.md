closures example {#driver_syntax_closures-example}
==================================================
This document contains small examples of the usage of (lambda-)closures. For technical details see the @ref driver_syntax_closures "closure" doc. For hints when to use which type of closure, see the end of this doc.

Many Muds use 'details' to add more flavour. 'Details' are items which can be looked at, but are not implemented as own objects, but instead simulated by the environment. Lets assume that the function

~~~{.c}
AddDetail(string keyword, string|closure desc)

~~~
adds the detail 'keyword' to the room, which, when look at, returns the string 'desc' resp. the result of the execution of closure 'desc' as the detail description to the player.

Now imagine that one wants to equip a room with magic runes, which read as `'Hello <playername>!\n"` when looked at. Obviously

~~~{.c}
AddDetail("runes", sprintf("Hello %s!\n", this_player()->QueryName()));

~~~
is not sufficient, as the `this_player()` is executed to early and just once: for the player loading the room.

The solution is to use closures. First, the solution using lfun-closures:

~~~{.c}
private string _detail_runes () {
  return sprintf("Hello %s!\n", this_player()->QueryName());
}
...
AddDetail("runes", #'_detail_runes);

~~~
or with an inline closure:

~~~{.c}
AddDetail(
  "runes",
  (: sprintf("Hello %s!\n", this_player()->QueryName()) :)
);

~~~
Simple? Here is the same code, this time as lambda-closure:

~~~{.c}
AddDetail(
  "runes",
  lambda(
    0,
    ({
      #'sprintf,
      "Hello %s!\n",
      ({#'call_other, ({#'this_player}), "QueryName" })
    })
  )
);

~~~
Why the extra `({ })` around `#'this_player`? `#'this_player` alone is just a symbol, symbolizing efun::this_player(), but efun::call_other() needs an object as first argument. Therefore, the `#'this_player` has to be interpreted as function to evaluate, which is enforced by enclosing it in `({ })`. The same reason also dictates the enclosing of the whole `#'call_other` expression into `({ })`. Note also the missing `#'return`: it is not needed. The result of a lambda-closure is the last value computed.

Another example: Task is to reduce the HP of every living in a room by 10, unless the result would be negative. Selecting all livings in a room is simply:

~~~{.c}
filter(all_inventory(room), #'living)

~~~
The tricky part is to reduce the HP. Again, first the lfun-closure solution:

~~~{.c}
private _reduce_hp (object liv) {
  int hp;
  hp = liv->QueryHP();
  if (hp > 10){
    liv->SetHP(hp-10);
  }
}
...

map( filter(all_inventory(room), #'living), #'_reduce_hp)

~~~
or as an inline closure:

~~~{.c}
map(
  filter(all_inventory(room), #'living),
  (:
    int hp;
    hp = liv->QueryHP();
    if (hp > 10){
      liv->SetHP(hp - 10);
    }
  :)
);

~~~
Both efun::filter() and efun::map() pass the actual array item being filtered/mapped as first argument to the closure.

Now, the lambda-closure solution:

~~~{.c}
map(
  filter(all_inventory(room), #'living),
  lambda(
    ({ 'liv }),
    ({
      #', , // not obvious if this is one arg or two?
      ({ #'=, 'hp, ({#'call_other, 'liv, "QueryHP" }) }),
      ({
        #'?,
        ({#'>, 'hp, 10 }),
        ({ #'call_other, 'liv, "SetHP", ({#'-, 'hp, 10 }) })
      })
    })
  ) // of lambda()
);

~~~
It is worthy to point out how local variables like 'hp' are declared in a lambda-closure: not at all. They are just used by writing their symbol 'hp . Same applies to the closures parameter 'liv .

The lambda-closure solution is not recommended for three reasons: it is complicated, does not use the powers of efun::lambda(), and the efun::lambda() is recompiled every time this statement is executed!

So far, lambda-closures seem to be just complicated, and in fact: they are. Their powers lie elsewhere.

Imagine a computation, like for skill resolution, which involves two object properties multiplied with factors and then added.

The straightforward solution would be a function like:

~~~{.c}
int Compute (object obj, string stat1, int factor1, string stat2,
  int factor2)
{
  return (
    call_other(obj, "Query"+stat1) * factor1 +
    call_other(obj, "Query"+stat2) * factor2
  );
}

~~~
Each call to `Compute()` involves several operations (computing the function names and resolving each efun::call_other()) which in fact need to be done just once. Using lambda-closures, one can construct and compile a piece of code which behaves like a `Compute()` tailored for a specific stat/factor combination:

~~~{.c}
closure ConstructCompute (object obj, string stat1, int factor1,
  string stat2, int factor2)
{
  mixed code;

  // Construct the first multiplication.
  // The symbol_function() creates a symbol for the
  // lfun 'Query<stat1>', speeding up later calls.
  // Note again the extra ({ }) around the created symbol.

  code = ({#'*, ({ symbol_function("Query"+stat1, obj) }), factor1 });

  // Construct the second multiplication, and the addition
  // of both terms.

  code = ({
    #'+,
    code,
    ({#'*, ({ symbol_function("Query"+stat2, obj) }), factor2 })
  });

  // Compile the code and return the generated closure.
  return lambda(0, code);
}

~~~
Once the closure is compiled,

~~~{.c}
str_dex_fun = ConstructCompute(obj, "Str", 10, "Dex", 90);

~~~
it can be used with a simple `funcall(str_dex_fun)`.

## When to use which closure? #

First, a closure is only then useful if it needn't to live any longer than the object defining it. Reason: when the defining object gets destructed, the closure will vanish, too.

Efun-, lfun- and inline closures should be used where useful, as they mostly do the job and are easy to read. The disadvantage of lfun- and inline closures is that they make a efun::replace_program() impossible - but since such objects tend to not being replaceable at all, this is no real loss.

Lambda closures are needed if the actions of the closure are heavily depending on some data available only at runtime, like the actual inventory of a certain player.

If you use lfun-closures and find yourself shoving around runtime data in arguments or (gasp!) global variables, it is time to think about using a lambda-closure, compiling the value hard into it.

The disadvantages of lambda closures are clear: they are damn hard to read, and each efun::lambda() statement requires extra time to compile the closure.

@see @ref driver_syntax_closures "closure", @ref driver_syntax_closure_guide "closures"