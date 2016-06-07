foreach {#driver_LPC_foreach}
=============================
@usage{
// Call quit() in all interactive users
foreach(o : users()) o->quit();
foreach(object o : users()) o->quit();

// Print the contents of a mapping <m>
foreach(key, value : m) printf("%O:%O\n", key, value);
foreach(mixed key, mixed value : m) printf("%O:%O\n", key, value);

// Don't change the content of a string: s remains "FOOBAR".
s = "FOOBAR";
foreach(i : s) i += 32;

// Do change the content of a string: s will become "foobar".
s = "FOOBAR";
foreach(i : &s) i += 32;

// Count from 0 to 5
foreach(i : 6) printf("%d\n", i);

// Count from 1 to 6
foreach(i : 1 .. 6) printf("%d\n", i);
}

@history{
changed (3.3.44) -- introduced the use of references, the loop over an integer expression, and the loop over an integer range.
changed (3.3.266) -- added support for structs.
}

@see 
