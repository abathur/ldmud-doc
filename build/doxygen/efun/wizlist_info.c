public class efun {
   /**
    * Returns an array with the interesting entries of the wizlist. Needs to be privileged by the master object.
    * 
    * The result is an array with one entry for every wizard (uid). Every entry is an array itself:
    * 
    * string w[`WL_NAME`]           = Name of the wizard.
    * int    w[`WL_COMMANDS`]       = Weighted number of commands execute by objects of this wizard.
    * int    w[`WL_COST`]
    * int    w[`WL_GIGACOST`]       = Weighted sum of eval_costs.
    * int    w[`WL_TOTAL_COST`]
    * int    w[`WL_TOTAL_GIGACOST`] = Total sum of eval_costs.
    * int    w[`WL_HEART_BEATS`]    = Weighted count of heart_beats.
    * int    w[`WL_CALL_OUT`]       = Reserved for efun::call_out() (unused yet).
    * int    w[`WL_ARRAY_TOTAL`]    = Total size of arrays in elements.
    * int    w[`WL_MAPPING_TOTAL`]  = Total size of mappings in elements.
    * int    w[`WL_STRUCT_TOTAL`]   = Total size of structs in elements.
    * mixed  w[`WL_EXTRA`]          = Extra wizlist-info if set.
    * 
    * The 'weighted' entries decay every hour by 10%.
    * 
    * @headerfile <wizlist.h>
    * 
    * @synopsis{
    * mixed * wizlist_info()
    * }
    * 
    * @history{
    * changed (3.2.10) -- split the old WL_EVAL_COST into WL_COST and WL_GIGACOST to accomodate for longer uptimes, and introduced WL_TOTAL_COST/WL_TOTAL_GIGACOST.
    * changed (3.3.174) -- added WL_MAPPING_TOTAL.
    * changed (3.3.?) -- added WL_STRUCT_TOTAL.
    * }
    * 
    * @see master::privilege_violation(), efun::set_extra_wizinfo_size(), efun::get_extra_wizinfo(), efun::set_extra_wizinfo()
   **/
   mixed * wizlist_info();
}
