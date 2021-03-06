.. efun:: string implode(mixed *arr, string del)

  Concatenate all strings found in array :arg:`arr`, with the string :arg:`del` between each element. Only strings are used from the array.

  .. usage::

    This basic example inserts an asterisk between each array element::

      implode(({ "foo", "bar", "" }), "*") // returns "foo*bar*"

    Because implode ignores non-string elements, the result below only includes a single "b"::

      implode(({ "a", 2, this_object(), "c" }), "b") // returns "abc"

    Together with :efun:`explode` this can be used as a search-and-replace for strings::

      implode(explode("a short text", " "), "_") // returns "a_short_text"

    But nowadays you can also use::

      regreplace("a short text", " ", "_", 1)

  .. seealso:: :efun:`explode`, :efun:`regreplace`
