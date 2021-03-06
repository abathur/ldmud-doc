.. efun:: mixed * wizlist_info()
  :include: <wizlist.h>

  Returns an array with the interesting entries of the wizlist. Needs to be privileged by the master object.

  The result is an array with one entry for every wizard (uid). Every entry is an array itself:

    string w[:macro:`WL_NAME`]           = Name of the wizard.
    int    w[:macro:`WL_COMMANDS`]       = Weighted number of commands execute by objects of this wizard.
    int    w[:macro:`WL_COST`]
    int    w[:macro:`WL_GIGACOST`]       = Weighted sum of eval_costs.
    int    w[:macro:`WL_TOTAL_COST`]
    int    w[:macro:`WL_TOTAL_GIGACOST`] = Total sum of eval_costs.
    int    w[:macro:`WL_HEART_BEATS`]    = Weighted count of heart_beats.
    int    w[:macro:`WL_CALL_OUT`]       = Reserved for :efun:`call_out` (unused yet).
    int    w[:macro:`WL_ARRAY_TOTAL`]    = Total size of arrays in elements.
    int    w[:macro:`WL_MAPPING_TOTAL`]  = Total size of mappings in elements.
    int    w[:macro:`WL_STRUCT_TOTAL`]   = Total size of structs in elements.
    mixed  w[:macro:`WL_EXTRA`]          = Extra wizlist-info if set.

  The 'weighted' entries decay every hour by 10%.

  :history 3.2.10 changed: split the old :macro:`WL_EVAL_COST` into :macro:`WL_COST` and :macro:`WL_GIGACOST` to accomodate for longer uptimes, and introduced :macro:`WL_TOTAL_COST`/:macro:`WL_TOTAL_GIGACOST`.
  :history 3.3.174 changed: added :macro:`WL_MAPPING_TOTAL`.
  :history 3.3.? changed: added :macro:`WL_STRUCT_TOTAL`.

  .. seealso:: :master:`privilege_violation`, :efun:`set_extra_wizinfo_size`, :efun:`get_extra_wizinfo`, :efun:`set_extra_wizinfo`
