Listed herein are language incompatibilites between 3.3 and 3.5,
that you should pay attention to when updating.

- LPC features
  + structs are always supported.
    __LPC_STRUCTS__ is always defined.
  + inline closures are always supported.
    __LPC_INLINE_CLOSURES__ is always defined.
  + call-other on arrays is always supported.
    __LPC_ARRAY_CALLS__ is always defined.
  + alists are no longer supported.
    __ALISTS__ was removed.

- sefun prefix:
  The 3.5 driver allows to explicitly call simul-efuns using a 'sefun::'
  prefix, e.g. sefun::fun(). If a program has inherited another
  program with the name "sefun" and explicitly called inherited
  lfuns with that syntax, this won't work anymore, because the
  driver now tries to find a simul-efun with that name.
  This also applies to symbol_function and closure literals (#'sefun::fun).

- ptmalloc keywords for debug_info():
  DID_MEM_MMAP, DID_MEM_MMAP_SIZE, DID_MEM_FREE_CHUNKS, DID_MEM_FFREE,
  DID_MEM_FFREE_SIZE, DID_MEM_MAX_ALLOCATED and DID_MEM_KEEP_COST were
  removed.

- Removed efuns:
  + The deprecated efuns cat() and tail() were removed. They can be
    easily and more flexibly replaced by sefuns, which are supplied with
    the driver in /mudlib/deprecated/. (#637, #228)
  + The efun set_light() was removed. This includes the internal light
    state managment in the driver. The mudlib does a better and more
    flexible job at managing light in/from objects. (#775)
  + The supporting efuns for alists were removed: insert_alist, order_alist,
    intersect_alist, assoc.

- New efuns:
  + json_parse() parses strings encoding a JSON object into an
    appropriate LPC value. (optional efun)
  + json_serialize() converts a LPC value into an JSON object and
    serializes it as LPC string. (optional efun)

- Changed efuns:
  + call_other() and call_direct() now always accept an array of objects or
    strings (object names) as argument and call the function in all of these
    objects.
  + object_info() does not report OIB_TOTAL_LIGHT any more, therefore the
    array OINFO_BASIC is one element shorter.

- Pragmas
  + The behaviour of the pragma combine_strings is mandatory, that means
    string literals concatenated by '+' will always be combined at
    compile-time. This pragmas and no_combine_strings are ignored. (#702)
  + The behaviour of the pragma local_scopes is mandatory, that means
    that variables defined in a block always cease to exist after the end of
    the block. This pragma and no_local_scopes are ignored  (#702)
  + The behaviour of the pragma verbose_errors is mandatory, the compiler will
    always give information about the context of an error.
    This pragma is ignored  (#702)
  + The pragma warn_deprecated is now enabled by default. (#702)

- 'deprecated' modifier
  The deprecated modifier can be used for lfuns (and sefuns) and global
  variables. Upon creating and closure to them or using/calling them the
  compiler will issue a warning. The same occurs in symbol_function(),
  symbol_variable() and call_other/call_direct/call_resolved().

- LPC types
  + the 'float' type on 64 bit platforms (specifically LP64) has a higher
    precision and larger value ranges, because the driver uses the native
    'double' types of the host system to store them. On most host systems they
    conform to the IEEE 754 double precision floating point format.
    WARNING: If you want to save them losslessly with save_object/save_value(),
             you MUST use savefile format version 2 or higher!



