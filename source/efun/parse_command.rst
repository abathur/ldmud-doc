.. efun:: int parse_command(string cmd, object  env, string fmt, mixed &var, ...)
  int parse_command(string cmd, object *arr, string fmt, mixed &var, ...)
  :optional:

  :efun:`parse_command` is basically a spiffed up sscanf operating on word basis and targeted at recognizing object descriptions from command strings.

  .. todo:: above description sucks for newer users; this should just describe what the function does

  The efun takes the command string :arg:`cmd` and the object(s) :arg:`env`/:arg:`arr` and tries to match it against the format string :arg:`fmt`. Successfully matched elements are assigned to the variables :arg:`var`.... The result from the efun is 1 if the command could be fully matched, and 0 otherwise.

  If the objects are given as a single object :arg:`env`, the efun matches against the given object and all objects contained therein. Otherwise, if the objects are given as an array :arg:`arr` of objects, the efun matches only against the given objects.

  The format string :arg:`fmt` consists of words, syntactic markers, and %-directives for the values to parse and return in the variables. A typical example is `` 'get' / 'take' %i `` or `` 'spray' / 'paint' [paint] %i ``. The elements in detail are:

     'word': obligatory text
     [word]: optional text
     /     : Alternative marker
     %o    : Single item, object
     %s    : Any text
     %w    : Any word
     %p    : One of a list of prepositions.
             If the variable associated with %p is used to pass
             a list of words to the efun, the matching will take
             only against this list.
     %l    : non-compat: Living objects
             compat: a single living object
     %i    : Any objects
     %d    : Number >= 0, or when given textual: 0-99.

  .. todo:: turn into enumerate? consier same re: lists below

  A *word* in this context is any sequence of characters not containing a space. 'living objects' are searched by calls to the (simul)efuns ``find_player()`` and ``find_living()``: both functions have to accept a name as argument and return the object for this name, or 0 if there is none.

  The results assigned to the variables by the %-directives are:

     %o : returns an object
     %s : returns a string of words
     %w : returns a string of one word
     %p : if passed empty: a string
          if passed as array of words: var[0] is the matched word
     %i : returns an array with the following content:
            [0]: int: the count/number recognized in the object spec
                      > 0: a count (e.g. 'three', '4')
                      < 0: an ordinal (e.g. 'second', 'third')
                      = 0: 'all' or a generic plural such as 'apples'
            [1..]: object: all(!) objects matching the item description.
                           In the :arg:`env` form this may be the whole
                           recursive inventory of the :arg:`env` object.
          It is up to the caller to interpret the recognized numeral
          and to apply it on the list of matched objects.
     %l : non-compat: as %i, except that only living objects are
                      returned.
          compat: as %o, except that only a living object is returned.

  %i (and non-compat-%l) match descriptions like 'three red roses', 'all nasty bugs' or 'second blue sword'.

  .. note:: Patterns of type: "%s %w %i" might not work as one would expect. %w will always succeed so the arg corresponding to %s will always be empty.

  To make the efun useful it must have a certain support from the mudlib: it calls a set of functions in objects to get the information it needs to parse a string.

    1. string *parse_command_id_list()
        Normal singular names of the object.

    2. string *parse_command_plural_id_list() - optional
        Plural forms of the names returned by 1. If this function doesn't exist, the parser tries to pluralize the names returned by 1.

    3. string *parse_command_adjectiv_id_list() -  optional
        All adjectives associated with this object.

  All names and adjectives may consist of several words separated by spaces.

  These functions should exist in all objects and are therefore best put into a mandatory inherit file (e.g. /std/object.c).

  In addition the master object may offer the same functions to provide reasonable defaults (like 'thing' as generic singular name):

       string *parse_command_id_list()
         - Would normally return: ``({ "one", "thing" })``

       string *parse_command_plural_id_list()
         - Would normally return: ``({ "ones", "things", "them" })``

       string *parse_command_adjectiv_id_list()
         - Would normally return ``({ "iffish" })``

  Two additional functions in the master object provide the default list of prepositions (needed for %p) and the single 'all' word:

       string *parse_command_prepos_list()
         - Would normally return: ``({ "in", "on", "under", "behind", "beside" })``

       string parse_command_all_word()
         - Would normally return: "all"

  .. usage::

    ::

      object *items;
      parse_command("take apple",environment(this_player()),
                    " 'get' / 'take' %i ", items);

  :history 3.3.258 changed: removed the compat-mode parse_command().

  .. seealso:: :efun:`sscanf`
