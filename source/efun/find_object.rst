.. efun:: object find_object(string str)

Find an object with the object_name str. If the object isn't loaded,
it will not be found.

EXAMPLES
object obj;
obj = find_object("std/thing");
obj = find_object("std/thing.c");
obj = find_object("/std/thing");
obj = find_object("/std/thing.c");

All four statements are equal.

obj = find_object("/std/thing#42");

returns the clone whose object_name is "std/thing#42", if
it exists.

  .. seealso:: :efun:`object_name`, :efun:`to_object`
