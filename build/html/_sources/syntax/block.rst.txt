.. syntax:: {[<statement>...]}
  :name: block
  :topics: flow control

  A block is a special statment, that begins with ``{``, contains a list of statements, and ends with ``}``.

  The block may define local variables. If for a variable no initialisation is given, the variable is initialised to 0 every time the block is entered. Otherwise, the initialisation expression is evaluated and its result assigned to the variable everytime the block is entered.

  Example definitions are::

    int i;
    int j = 3;
    int k = 3 * j, l;

    Here, i and l are both initialised to 0; j is initialised
    to 3, and k is initialised to 9 (3 * j).

  Local variables defined in a block are visible only until the end of the block. Definitions in an inner block hide definitions in outer blocks.

  .. note:: Up to 3.2.7 local variables were visible (from their point of definition) in the whole function. That is, code like::

      do {
        int res;
        res = ...
      } while (res == 5);
      write(res);

    was perfectly legal. It is no longer, as ``res`` ceases to exist with the closing ``}`` of the :keyword:`while`.

    .. todo:: Would the semantics work better if the above should reference a while statement or while block?

  :history 3.2.7 changed: local variables were visible (from their point of definition) within the containing function scope; now they will cease to exist when any containing block is closed
  :history 3.2.8 changed: local variables can now be :concept:`initialised <initialisation>` when they are defined
  :history 3.5.0 changed: it is no longer possible to disable local scope behavior
