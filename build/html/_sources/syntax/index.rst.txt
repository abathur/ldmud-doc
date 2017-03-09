.. operator:: []
  mixed arr[index]
  int str[index]
  mixed * arr[from .. to]
  string str[from .. to]
  :topics: arrays, indexing, strings, mappings

  Return one element from a string/array (first form), or a slice (substring resp. subarray) of the string/array (second form).

  The indexes :part:`index`, :part:`from` and :part:`to` are numbered 0 to ``strlen(str)-1`` resp. ``sizeof(arr)-1``.

  If an index is written ``<value``, the value is counted from the end of the string/array and is numbered 1 to ``strlen(str)`` resp. ``sizeof(arr)``.

  If an index is written '>value', the value is counted from the end of the string/array if it is negative (starting with -1 for the last element), and from the beginning if it is positive (starting with 0 for the first element).

  If :part:`from` is omitted, it defaults to the beginning of the string/array. If :part:`to` is omitted, it defaults to the beginning of the string/array.

  In the first form, the :part:`index` must be within the bounds of the string/array, or a runtime error occurs. In the second form, the indexes will be fitted to the bounds of the string/array. If :part:`from` is greater than :part:`to`, or both outside the bounds, an empty string/array ("" resp. ``({})``) will be returned.

  The closure notation is straightforward:

  ================  ================================
  normal form       closure form
  ================  ================================
  ``[index]``       ``({'#[,      arr, index })``
  ``[<index]``      ``({'#[<,     arr, index })``
  ``[>index]``      ``({'#[>,     arr, index })``
  ``[from..to]``    ``({'#[..],   arr, from, to })``
  ``[<from..to]``   ``({'#[<..],  arr, from, to })``
  ``[from..<to]``   ``({'#[..<],  arr, from, to })``
  ``[<from..<to]``  ``({'#[<..<], arr, from, to })``
  ``[>from..to]``   ``({'#[>..],  arr, from, to })``
  ``[from..>to]``   ``({'#[..>],  arr, from, to })``
  ``[>from..<to]``  ``({'#[>..<], arr, from, to })``
  ``[<from..>to]``  ``({'#[<..>], arr, from, to })``
  ``[>from..>to]``  ``({'#[>..>], arr, from, to })``
  ================  ================================

  .. todo:: could break the below out into separate parts, but the first section is demonstrating a symmetry that might make a table better?

  .. usage::

    ::

      foo = ({ 1, 2, 3, 4 });         str = "test";

      foo[1]     -> 1                 str[1] -> 'e' == 101
      foo[1..2]  -> ({ 2, 3 })        str[1..2]  -> "es"
      foo[2..1]  -> ({ })             str[2..1]  -> ""
      foo[0..<2] -> ({ 1, 2 })        str[0..<2]  -> "tes"
      foo[..<2]  -> ({ 1, 2 })        str[..<2]  -> "tes"
      foo[<3..]  -> ({ 2, 3, 4 })     str[<3..]  -> "est"

      foo[1] = 5                // foo == ({ 1, 5, 3, 4 })
      foo[1..2] = ({ 5, 6, 7 }) // foo == ({ 1, 5, 6, 7, 4 })
      foo[1..2] = ({ })         // foo == ({ 1, 4 })

      str[1] = 'a'              // str == "tast"
      str[1..2] = "bar"         // str == "tbart"
      str[1..2] = ""            // str == "tt"

  .. warning:: The ``slice_array()`` efun was the old form of :operator:`[]` on arrays. Efun ``extract()`` was the old form of the :operator:`[]` on strings. Both *are no longer supported* and should not be used anymore!

  .. todo:: update above? They've been removed since 3.3...

  :history 3.1.K changed: The syntax for "counting from last element" has changed between from ``-1`` to ``<1``. ``foo[0..-1]`` is now an empty string resp. array.
  :history 3.3 changed: introduced the '>' indexing method.

  .. seealso:: :efun:`member`, :efun:`sizeof`

