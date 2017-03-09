.. command:: ed

  The :command:`ed` command opens a text editor. Ed has two modes, command mode and insert mode. Command mode uses ``:`` for a prompt, while insert mode has no prompt. You exit insert mode by typing a single ``.`` on a line.

  .. note:: These manpages seem a bit antique, though still correct. For a better detailed help, invoke ed and use the ``h`` command. Also you could look into the man page for ed(1) on your nearest Unix box. And for a bit of fun you can try the good old quiz(6), invoke as ``quiz function ed-command``.

  .. subtopic:: syntax forms

    All commands entered in either mode use one of the following syntax forms. With a line range::

      <X>,<Y><cmd>

    With a single line::

      <X><cmd>

    Or with no line specified::

      <cmd>

    To print lines 1 to 10, fill the first form with ``1`` and ``10`` and ``p``::

      1,10p

    To delete lines 1 to 5, fill the first form with ``1``, ``5`` and ``d``::

      1,5d

    To print a single line, fill the second form with ``8`` and ``p``::

      8p

    A ``.`` is the "current line". The current line is the last line referenced. If you want to print last line + 10 more::

      .,.+10p

  .. subtopic:: command mode commands

    Commands that use a line range (if no line is given, then curent line is printed):

    ``p``
      Print line.
    ``d``
      Delete line.
    ``l``
      Print line with control characters.
    ``r file``
      Read in a file after the line specified.
    ``s``
      Substitute patterns. See special documentation.
    ``z``
      Print 10 lines.
    ``a``
      Start insert mode after specified line. Exit with ``.<return>``.
    ``i``
      Start insert mode before specified line. Exit with ``.<return>``.

    Commands used without line specification:

    ``q``
      Quit. Won't work if file is changed.
    ``Q``
      Quit and discard all changes if not saved.
    ``w``
      Write the file out.
    ``w file``
      Write the file out with name ``file``.
    ``e file``
      Edit a file.
    ``!cmd``
      Give a game command. For example "say Wait, I am busy".

    As line numbers ``.`` is current line, and ``$`` is last line of file. Thus ``1,$p`` will always print all of the file.

  .. subtopic:: substitutions

    Substitutions are very advanced.

    First a simple example:

    ``s/apa/bepa/``
      This will substitue the ``apa`` in current line with ``bepa``. If ``p`` is appended, you will also immediately see the result.

    ``1,$s/apa/bepa/``
      Same, but all lines in file. Only first occurence on every line.

    Any character can used instead of ``/``::

      s!apa!bepa!g

    The ``g`` specifies that all occurences of apa on this line are changed to bepa, instead of just the first.

    The replacement pattern can be a regular expression, as covered in the next section.

  .. subtopic:: searching

    Searching is done with::

      /hello/

    This will find first match in or after current line. To repeat the search, use::

      //

    The patterns are regular expressions, where some characters have a special meaning:

    ``.``
      Match any character.
    ``x*``
      Match any numbers of x (0 or more).
    ``[abc]``
      Match ``a``, ``b`` or ``c``.
    ``[0-9]``
      Match any digit 0 - 9.
    ``[a-z]``
      Match any lowercase letter.
    ``\x``
      Match ``x`` where ``x`` can be any character except ``(`` and ``)``.

    .. usage::

      Substitute any string ``abXd`` against ``ABCD`` where X can be any
      character::

        s/ab.d/ABCD/

    .. note:: This only half the truth, there is lots more magic in the regexps.

    .. seealso:: :efun:`regexp`

  .. subtopic:: copying

    How to copy from a standard file.

    Enter ed. Then do ``r /room/vill_green.c``. Now you have something in the buffer. Change it into what you want it to be. Then ``w /players/peter/hall.c``. Or ``w hall.c``.

  .. subtopic:: insert mode commands

    ``=``
      prints current line
    ``a``
      append lines
    ``c``
      change, that is, delate, than insert
    ``d``
      delete line(s)
    ``E <filename>``
      discard current buffer and edit the file named <filename>
    ``e <filename>``
      like e, but refuse if file has been changed
    ``f``
      print current filename
    ``f <filename>``
      set filename
    ``i``
      insert line(s)
    ``j``
      with no or one argument: join line with following line

      with two arguments: join line range given
    ``k<letter>``
      set mark <letter> to current line. <letter> must be in the range [a-z] . The mark can be used thereinafter as a line address, with a leading slash. (e.g. ka to set mark a, /ap to print marked line)
    ``l``
      print line with control characters
    ``<start>,<end>m<dest>``
      move block (lines from start to end) behind line # dest
    ``<line>m<dest>``
      move single line
    ``m<dest>``
      move current line
    ``M``
      remove Ctrl-M (CR) characters.
    ``p``
      print line
    ``P``
      print line
    ``Q``
      quit, discarding the buffer
    ``q``
      the same, but refuse if file has been changed since last write
    ``r``
      read in file. If no adress is given, at the last insert position, if also nothing was inserted, at the end of the buffer
    ``s``
      substitute
    ``<start>,<end>t<dest>``
      copy block ( lines from start to end ) behind line position dest
    ``<line>t<dest>``
      copy single line
    ``t<dest>``
      copy current line
    ``w``
      write file
    ``W``
      write file
    ``x``
      write file if buffer has been changed since last change, then quit
    ``z``
      show approx. a screenful of lines

  .. subtopic:: tips & tricks

    .. This is the list of extended ed commands that Xio unearthed somewhere, thanks!

    a. never use ``1,$p`` to print out an editfile, because you will be thrown out 'cause of too much text transfereed to you.

    b. ``$``: jump to end of file.

    c. ``?anything?`` and ``??`` : search from bottom to up. (like '/' from beginning to end of file. (also with substitutions, try it out...)

    d. ( ``g/xxx/p`` search global xxx and print corresponding lines, ``/xxx/s/new/old/p`` : search xxx, substitute new to old in this line and print out. (try this concatenations with other commands)

    e. ``1,nmx`` ( see ed5 ), but also: ``1,ntx`` : don't move the lines, but make a copy of them.

    f. ``x,y w name`` : save lines ``x`` to ``y`` to ``file`` name (if you don't know the line numbers : ``=`` current line number)

    g. ``s/$/text/p`` : append text to the end of current LINE and print line

    h. ``s/^/text/p`` : insert text at beginning of current LINE and print line

  .. seealso:: :efun:`ed`
