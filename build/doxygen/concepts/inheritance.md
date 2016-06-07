inheritance {#driver_concepts_inheritance}
==========================================
Have you noticed how many objects in the system have the same functionality in common? Let's look at rooms for instance, they all have the ability to host people and provide commands. It's not that every room is programmed with the same basic functions again and again, rather it will use a model room and then make some special changes to it. That doesn't work by copying the file.. Ouch! Don't replicate code! But by putting a tiny inherit declaration:

~~~{.c}
inherit "<model-class>";

~~~
at the beginning of your new file. This must come before any local variables or functions. Once inherited your class will behave just like the model class, because all the public methods are available to the outside world. Now it is in your hands to change such an inherited behaviour. You have the following tools to do so:

## ACCESS TO VARIABLES #

It is one of the best design decisions in LPC that variables are not accessible from outside, but you can use inherited variables just as if they were your own. Modifiers apply however.

## METHOD OVERLOADING #

You can simply rewrite a method that is also defined in the model class, and thus change how it behaves:

~~~{.c}
int method_that_also_exists_in_the_model() {
  <your new code>
}

~~~
Contrary to other languages in LPC method overloading only matches the name of the method, so even by changing the amount and type of parameters you will mask out the original version of the method. You can even apply other modifiers to it as the original.

## EXAMPLE #

Let's imagine very simple food in a file called "/the/food.c":

~~~{.c}
// unless "modified" variables are accessible by inheritors
int vitamins = 10;

// please overload this function with your own description
public short() { return "something edible"; }

// let's do some standard action for food
public consume() {
  this_player() -> nourish(vitamins);
  destruct(this_object());
}

~~~
And now someone else decides to do some italian cooking in a file called "/the/fusilli.c":

~~~{.c}
inherit "/the/food";

// we have our own variables.
int gone_cold = 0;

// and we simply redefine the short() function to replace it
public short() {
  // description changes depending on gone_cold
  return "a "+( gone_cold ? "stinking" : "steaming" )+" plate of fusilli";
}

// we have a new function to make food go cold
private deteriorate() {
  gone_cold = 1;
  write("The fusilli have gone cold.\n");
}

// assume this gets called at creation
private create() {
  // we can access the variable we inherited from food.c
  vitamins = 44;           // tomato has plenty of vitamins

  // go cold in 5 minutes
  call_out( #'deteriorate, 5 * 60 );
}

// we can overload the function even with new parameters
public consume(how) {
  // fetch the name of the person, or use "Someone"
  string name = this_player() -> name() || "Someone";

  if (!gone_cold) {
    write("You enjoy a delicious plate of fusilli.\n");
    say(name +" guzzles a plate of hot fusilli.\n");
  }
  else if (how == "quickly") {
    write("You eat the fusilli so quickly you hardly notice they have gone cold.\n");
    say(name +" wolfs down a plate of cold fusilli.\n");
  }
  else {
    write("You eye the plate and wonder if you really feel like eating cold fusilli.\n");
    return; // don't eat
  }

  // and here comes the most important part:
  // we execute consume() from food.c, so we
  // actually inherit its behaviour.
  ::consume();
}

~~~

## ADVANCED USAGE #

### DOING MULTIPLE INHERITANCE #

While the Java(TM) language has so-called interfaces as a kludge, LPC doesn't need them as it supports real multiple inheritance. A very powerful feature, it lets you combine the behaviour of several classes into a new one. Simply put several lines of inherit declarations underneath each other. If you have name collisions in the namespace of inherited methods, you will have to address them explicitely with a "the/file"::method(args) syntax.

## ADVANCED EXAMPLE #

~~~{.c}
inherit "foo";
inherit "bar";
inherit "baz";
inherit "ball";

reset() {
  "ba?"::reset();
  // calls bar::reset() and baz::reset()

  "ba*"::reset();
  // calls bar::reset(), baz::reset() and ball::reset()

  "*"::reset();
  // calls every inherited reset() function.

  "ball"::rejoice("Listen to italectro today!");
  // only explicit filename of model class allows
  // passing arguments to the inherited method
}

~~~

AUTHOR:

~~~{.c}
symlynX of PSYC and Nemesis, with a little help from Someone

~~~

@see @ref driver_LPC_functions "functions", @ref driver_concepts_initialisation "initialisation", @ref driver_LPC_modifiers "modifiers", @ref driver_LPC_pragma "pragma", @ref driver_concepts_overloading "overloading", efun::function_exists(), efun::functionlist(), efun::inherit_list(), efun::symbol_variable(), efun::variable_exists(), efun::variable_list()