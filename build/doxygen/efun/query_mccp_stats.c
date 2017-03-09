public class efun {
   /**
    * This efun gives you statistics about current compression of the player ( default `this_player()` ).
    * 
    * You get an array with `({ uncompressed bytes , compressed bytes })`. If the connection is not compressed it returns 0.
    * 
    * It raises an error on not-interactive objects.
    * 
    * Available only if the driver is compiled with @ref driver_topics_mccp "MCCP" enabled; @ref driver_topics_predefined "__MCCP__" is defined in that case.
    * 
    * @synopsis{
    * int * query_mccp_stats()
    * int * query_mccp_stats(object player)
    * }
    * 
    * @history{
    * introduced (3.3.447)
    * backported (3.2.10)
    * }
    * 
    * @see efun::end_mccp_compress(), efun::start_mccp_compress(), efun::query_mccp()
   **/
   int * query_mccp_stats(object player);
}
