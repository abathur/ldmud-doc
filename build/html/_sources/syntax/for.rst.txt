.. keyword:: for
  for(<init>; <expr2>; <expr3>) statement;
  :topics: keyword

  Execute :part:`init` once. Then, while :part:`expr2` returns a non-zero value, execute :part:`statement`. Every time :part:`statement` has been executed, or a :keyword:`continue` statement has been executed, execute :part:`expr3` before next loop.

  :part:`init` is usually a series of one or more expressions (remember that assignments are expressions, too), separated by commas. Additionally it is also allowed to define new local variables here and assign them an initial value. The scope of such variables is the whole for statement.

  .. usage::

    Examples for legal :part:`init` expressions are::

      for (i = 0; ...
      for (i = 0, j = 0; ...
      for (i = 0, int j = i; ...
      for (int j = 4; ...

    Illegal :part:`init` expressions are::

      for (int i; ...      // no value assigned
      for (int i += 4; ... // only plain assignments allowed

    A :keyword:`break` in the :part:`statement` will terminate the loop. A :keyword:`continue` will continue the execution from the beginning of the loop.

  .. seealso:: :keyword:`foreach`, :keyword:`if`, :keyword:`do-while`, :keyword:`while`, :keyword:`switch`

  .. todo:: above, still probably some lang-related directive refinements needed; do-while isn't really a keyword; I'm kinda fudging--it's a do-while statement, built atop both the "do" and "while" keywords (but "do" isn't used in any other statement.)
