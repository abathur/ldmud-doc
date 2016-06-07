.. driver:: invocation
  :synopsis: Description of the invocation of the gamedriver, especially of the command arguments. This document describes the commandline version of the driver only; non-commandline versions are platform specific and described in the related documentation.

  .. todo:: in this document, any references to compile options need to be properly linked/refd

  .. todo:: non-zero chance that the use of std domain features like program/option will create subtle issues later when attempting to xref these

  .. todo:: search for a few keywords like compile to hunt down documentation that refers to configure/build/compile-time options for the driver

  .. program:: ldmud

  The driver is invoked from the commandline as other normal programs. Neither the current directory nor the directory the executable is in need to be in any special relation the directory of the mudlib. Once the driver is running, it emits two streams of outputs:

  - driver-related messages on stderr; this unfortunately includes LPC compiler diagnostics
  - LPC runtime-related messages in the logfile <mudlib>/<host>.parse.log (the name can be changed).

  It is possible to start the driver without any commandline arguments as suitable defaults are specified at compile time. The invocation syntax is::

    driver [options] [<portnumber>]...

  <portnumber> the number of the port the driver shall use to accept connections. The maximum number of ports is determined by MAXNUMPORTS in the source file config.h.

  The options modify the behaviour of the gamedriver. Some of them are only available if a certain compile-time option was enabled (typically in the source file config.h). The following options are recognized:

  .. option:: -P, --inherit <fd-number>

    Inherit filedescriptor <fd-number> from the parent process as socket to listen for connections. Only available if compiled with MAXNUMPORTS.

  .. option:: -u, --udp <portnumber>

    Specify the <portnumber> for the UDP port, overriding the compiled-in default. Only available if compiled with CATCH_UDP_PORT.

  .. option:: -D, --define <macro>[=<text>]

    Add <macro> (optionally to be expanded to <text>) to the list of predefined macros known by the LPC compiler.

  .. option:: -E, --eval-cost <ticks>

    Set the number of <ticks> available for one evaluation thread. If 0, execution is unlimited.

  .. option:: -M, --master <filename>

    Use <filename> for the master object.

  .. option:: -m, --mudlib <pathname>

    Use <pathname> as the top directory of the mudlib.

  .. option:: --debug-file <filename>

    Log all debug output in <filename> instead of <mudlib>/<host>.debug.log .

  .. option:: --hostname <name>

    Use <name> as hostname instead of what the system says.

  .. option:: --hostaddr <addr>

    Use <addr> as address of this machine, instead of what the system says. In particular this address will be used to open the driver ports.

  .. option:: --no-compat

  .. option:: --compat

    Select the mode (plain or compat) of the driver. This choice does not affect the default name of the master object.

  .. option:: -d, --debug

    Generate debug output; repeat the argument for even more output:
      * ``>= 1``: log resets, clean ups, swaps, reception of urgend data, telnet negotiation states. check_a_lot_of_refcounts() on startup when swapping of variables is disabled.
      * ``>= 2``: log all add_message()s, name lookup failures, new players.
      * ``>= 3``: progress of garbage collection
      * ``>= 4``: even more junk from garbage collection

  .. option:: -c, --list-compiles

    List the name of every compiled file on stderr.

  .. option:: -e, --no-preload

    Pass a non-zero argument (the number of occurences of this option) to :master:`preload`, which usually inhibits all preloads of castles and other objects.

  .. option:: --erq <filename>, --erq "<filename> <erq args>"

    Use <filename> instead of 'erq' as the basename of the ERQ executable. If the name starts with a '/', it is take to be an absolute pathname, otherwise it is interpreted relative to <bindir>. If not specified, 'erq' is used as the executable name.

    By enclosing the argument value in quotes, it is possible to pass arguments (e.g. --execdir) to the erq. These arguments however must not contain embedded spaces.

  .. option:: -N, --no-erq

    Don't start the erq demon (if it would be started at all).

  .. option:: --alarm-time <seconds>

    Set the granularity of call_out() and heartbeat timing. Minimum value is 1.

  .. option:: --heart-interval <seconds>

    Set the interval between two heartbeats. Minimum value is 1.

  .. option:: --sync-heart

    All heartbeats occur at the same time (modulo granularity).

  .. option:: --async-heart

    Heartbeats occur when they are due (modulo granularity).

  .. option:: -t, --no-heart

    Disable heartbeats and call_outs.

  .. option:: -f, --funcall <word>

    The lfun master->flag() is called with <word> as argument before the gamedriver accepts netword connections.

  .. option:: --regexp pcre | traditional

    Select the default regexp package.

  .. option:: --max-array <size>

    The maximum number of elements an array can hold. Set to 0, arrays of any size are allowed.

  .. option:: --max-mapping <size>

    The maximum number of elements a mapping can hold. Set to 0, mappings of any size are allowed.

  .. option:: --max-mapping-keys <size>

    The maximum number of entries a mapping can hold. Set to 0, mappings of any size are allowed.

  .. option:: --max-callouts <size>

    The maximum number of callouts at one time. Set to 0, any number is allowed.

  .. option:: --max-bytes <size>

    The maximum number of bytes one read_bytes()/write_bytes() call can handle. Set to 0, reads and writes of any size are allowed.

  .. option:: --max-file <size>

    The maximum number of bytes one read_file()/write_file() call can handle. Set to 0, reads and writes of any size are allowed.

  .. option:: --max-thread-pending <size>

    The maximum number of bytes to be kept pending by the socket write thread. Set to 0, an unlimited amount of data can be kept pending.

    This option is ignored if pthreads are not used.

  .. option:: --cleanup-time <time>

    The idle time in seconds for an object before the driver tries to clean it up. It should be substantially longer than the reset time. A time <= 0 disables the cleanup mechanism.

  .. option:: --reset-time <time>

    The time in seconds before an object is reset. A time <= 0 disables the reset mechanism.

  .. todo:: sphinx doesn't like the way we document these -s flags below. It wants to add index/ref targets for the flag, so it throws 3 warnings for duplicate -s options here. It supports combining more than one syntax in a def with commas as we do, but that leaves no good way for providing separate descriptions. My only idea atm is to only pass the long form in to the flag, and then note the short form in the body; (i.e., only solution is to cheat)

  .. option:: --swap-time <time>, --swap-variables <time>

    Time in seconds before an object (or its variables) are swapped out. A time less or equal 0 disables swapping.

  .. option:: --swap-file <name>

    Swap into file '<name>' instead of '<mudlib>/LP_SWAP.<host>'.

  .. option:: --swap-compact

    Reuse free space in the swap file immediately. Giving this option results in smaller, but also more fragmented swapfiles, and the swap performance may degrade.

  .. option:: -s <time>, -s v<time>, -s f<name>, -s c

    Short alias for respective swap options (:option:`--swap-time`, :option:`--swap-variables`, :option:`--swap-file`, :option:`--swap-compact`).

  .. option:: --hard-malloc-limit <size>

    Restrict total memory allocation to <size> bytes. A <size> of 0 or 'unlimited' removes any restriction.

  .. option:: --soft-malloc-limit <size>

    This value gives a soft limit of the allocated memory (kind of low watermark). If this value is exceeded, the driver will call low_memory() in the master to inform the mudlib about the (potentially) developing low memory situation. A <size> of 0 or 'unlimited' removes this threshold.

  .. option:: --min-malloc <size>

  .. option:: --min-small-malloc <size>

    Determine the sizes for the explicit initial large resp. small chunk allocation. A size of 0 disables the explicit initial allocations.

  .. option:: --reserve-user <size>, --reserve-master <size>, --reserve-system <size>
  .. option:: -r u<size>, -r m<size>, -r s<size>

    Reserve <size> amount of memory for user/master/system allocations to be held until main memory runs out.

  .. option:: --filename-spaces

  .. option:: --no-filename-spaces

    Allow/disallow the use of spaces in filenames.

  .. option:: --strict-euids

  .. option:: --no-strict-euids

    Enable/disable the enforced use of euids.

  .. option:: --share-variables

  .. option:: --init-variables

    Select how clones initialize their variables:
      - by sharing the current values of their blueprint
      - by initializing them afresh (using __INIT()).

  .. option:: --pidfile <filename>

    Write the pid of the driver process into <filename>.

  .. option:: --tls-key <pathname>

    Use <pathname> as the x509 keyfile, default is 'key.pem'. If relative, <pathname> is interpreted relative to <mudlib>.

  .. option:: --tls-cert <pathname>

    Use <pathname> as the x509 certfile, default is 'cert.pem'. If relative, <pathname> is interpreted relative to <mudlib>.

  .. option:: --tls-crlfile <pathname>

    Use <pathname> as the filename holding your certificate revocation lists. If relative, <pathname> is interpreted relative to <mudlib>.

  .. option:: --tls-crldirectory <pathname>

    Use <pathname> as the directory where your certificate revocation lists reside. If relative, <pathname> is interpreted relative to <mudlib>.

  .. option:: --tls-trustfile <pathname>

    Use <pathname> as the filename holding your trusted PEM certificates. If relative, <pathname> is interpreted relative to <mudlib>.

  .. option:: --tls-trustdirectory <pathname>

    Use <pathname> as the directory where your trusted PEM certificates reside, default is '/etc/ssl/certs'. If relative, <pathname> is interpreted relative to <mudlib>.

  .. option:: --wizlist-file <filename>

  .. option:: --no-wizlist-file

    Read and save the wizlist in the named file (always interpreted relative the mudlib); resp. don't read or save the wizlist.

  .. option:: --gcollect-outfd <filename>, --gcollect-outfd <num>

    Garbage collector output (like a log of all reclaimed memory blocks) is sent to <filename> (or inherited fd <num>) instead of stderr. Only available if compiled with MALLOC_smalloc.

  .. option:: --y, --yydebug

    Enable debugging of the LPC compiler. Only available if compiled with YYDEBUG.

  .. option:: --randomdevice <filename>

    Chooses the source of the seed for the random number generator. Default is /dev/urandom, Fall-back if <filename> is not readable is the system clock. If you want to seed the PRNG with a specific seed, you can use a filename with the seed and give it here instead of using --random-seed. (Note: the last one of --randomdevice and --random-seed wins!)

    .. todo:: the option ``--randominit`` mentioned above, and in the last item of the history section, doesn't exist nor can I readily find a time when it has. My best guess is that at one time during development of the feature but perhaps outside of present code history ``--randomdevice`` was *called* ``--randominit`` and based on this assumption I have changed it. I may, however, be wrong.

  .. option:: --random-seed <num>

    Seed value for the random number generator. If not given, the driver chooses a seed value on its own. This option is for debugging.

  .. option:: --check-state <lvl>

    Perform a regular simplistic check of the virtual machine according to <lvl>:
    - ``= 0``: no check
    - ``= 1``: once per backend loop
    - ``= 2``: at various points in the backend loop
    Only available if compiled with DEBUG.

  .. option:: --check-refcounts

    Every backend cycle, all refcounts in the system are checked. SLOW! Only available if compiled with DEBUG.

  .. option:: --gobble-descriptors <num>

    <num> (more) filedescriptors are used up. You'll know when you need it. Only available if compiled with DEBUG.

  .. option:: --check-strings

    Every backend cycle, all shared strings in the system are checked. SLOW! Only available if compiled with DEBUG and CHECK_STRINGS.

  .. option:: -V, --version

    Print the version of the driver and exit.

  .. option:: --options

    Print the version and compilation options of the driver and exit.

  .. option:: -h, -?, --help

    Display a command help and exit.

  .. option:: --longhelp

    Display a long command help and exit.

  .. option:: --args <filename>

    The driver reads and parses the given file and treats its contents as if given on the commandline right where the --args option occured. The file itself can again contain --args options.

  .. subtopic:: Argument Parser

    The parser analyses the commandline arguments given with the driver invocation and distinguishes 'options', which start with a ``-``, from proper arguments. Options are further distinguished by their name and may take an additional value. In general, options and arguments can be given in any order.

    Options are recognized in two forms. In the short form the option must be given as a single ``-`` followed by a single letter. In the long form, options start with ``--`` followed by a string of arbitrary length. The short options are case sensitive, the long options aren't. Most options can be specified in both the short and long form, but that is not mandatory. Examples: ``-r`` and ``--recursive``.

    If an option takes a value, it must follow the option immediately after a separating space or ``=``. Additionally, the value for a short option may follow the option without separator. Examples are: ``-fMakefile``, ``-f Makefile``, ``--file=Makefile`` and ``--file Makefile``.

    Short options may be collated into one argument, e.g. ``-rtl``, but of these only the last may take a value.

    The option ``--`` marks the end of options. All following command arguments are considered proper arguments even if they start with a ``-`` or ``--``.

    The arguments are usually taken from the commandline; but the parser is also able to read them from a textfiles, which can be nested. The content of the textfiles is broken down into words delimited by whitespace, which are then treated as given on the commandline at the place where the instruction to read the textfile stood.

    The file parser recognizes simple double-quoted strings, which must be contained on a single line. Additionally, the ``#`` character given by itself is a comment marker - everthing after the ``#`` until the end of the current line is ignored.

  :history 3.2.9 changed: added the :option:`--max-thread-pending`, :option:`--hostname`, :option:`--hostaddr`, :option:`--args` and :option:`--random-seed` options.
  :history 3.2.10 changed: added the :option:`--filename-spaces` option.
  :history 3.3.378 changed: added :option:`--share-variables`, :option:`--init-variables`.
  :history 3.3.475/3.2.11 changed: added :option:`--tls-key`, :option:`--tls-cert`.
  :history 3.3.672/3.2.11 changed: added :option:`--tls-trustfile`, :option:`--tls-trustdirectory`.
  :history 3.3.677 changed: added :option:`--max-mapping-keys`.
  :history 3.3.714/3.2.15 changed: added :option:`--tls-crlfile`, :option:`--tls-crldirectory`.
  :history 3.3.718 changed: added :option:`--randomdevice`.
