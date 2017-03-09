public class efun {
   /**
    * This efun returns current whether the client uses compression or not ( default `this_player()` ).
    * 
    * You will get either `TELOPT_COMPRESS` or `TELOPT_COMPRESS2` if the connection is compressed, or 0 if it isn't.
    * 
    * Available only if the driver is compiled with @ref driver_topics_mccp "MCCP" enabled; @ref driver_topics_predefined "__MCCP__" is defined in that case.
    * 
    * @synopsis{
    * int query_mccp()
    * int query_mccp(object player)
    * }
    * 
    * @history{
    * introduced (3.3.447)
    * backported (3.2.10)
    * }
    * 
    * @see efun::end_mccp_compress(), efun::start_mccp_compress(), efun::query_mccp_stats()
   **/
   int query_mccp(object player);
}
