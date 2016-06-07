public class efun {
   /**
    * @synopsis{
    * int query_mccp()
    * int query_mccp(object player)
    * }
    * 
   **/
   int query_mccp(object player);
}
This efun returns current whether the client uses compression
or not ( default this_player() ).

You will get either TELOPT_COMPRESS or TELOPT_COMPRESS2 if the
connection is compressed, or 0 if it isn't.

Available only if the driver is compiled with MCCP enabled;
__MCCP__ is defined in that case.

Added in LDMud 3.3.447, backported to LDMud 3.2.10.

      See Also: 
         efun::end_mccp_compress(), efun::start_mccp_compress(), efun::query_mccp_stats(),

   @ref driver_concepts_mccp "mccp"
