public class efun {
   /**
    * Returns an array with the interesting entries of the wizlist.
    * Needs to be privileged by the master object.
    * 
    * The result is an array with one entry for every wizard (uid).
    * Every entry is an array itself:
    * 
    * string w[WL_NAME]           = Name of the wizard.
    * int    w[WL_COMMANDS]       = Weighted number of commands execute by
    * 
    *    objects of this wizard.
    *    
    * int    w[WL_COST]
    * int    w[WL_GIGACOST]       = Weighted sum of eval_costs.
    * int    w[WL_TOTAL_COST]
    * int    w[WL_TOTAL_GIGACOST] = Total sum of eval_costs.
    * int    w[WL_HEART_BEATS]    = Weighted count of heart_beats.
    * int    w[WL_CALL_OUT]       = Reserved for call_out() (unused yet).
    * int    w[WL_ARRAY_TOTAL]    = Total size of arrays in elements.
    * int    w[WL_MAPPING_TOTAL]  = Total size of mappings in elements.
    * int    w[WL_STRUCT_TOTAL]   = Total size of structs in elements.
    * mixed  w[WL_EXTRA]          = Extra wizlist-info if set.
    * 
    * The 'weighted' entries decay every hour by 10%.
    * 
    * @headerfile <wizlist.h>
    * 
    * @synopsis{
    * mixed * wizlist_info()
    * }
    * 
   **/
   mixed * wizlist_info();
}