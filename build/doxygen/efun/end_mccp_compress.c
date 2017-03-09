public class efun {
   /**
    * This efun must be called inside an interactive player and stops the compression of the driver -> client traffic.
    * 
    * Returns non-zero on success, and zero on a failure.
    * 
    * Available only if the driver is compiled with @ref driver_topics_mccp "MCCP" enabled; @ref driver_topics_predefined "__MCCP__" is defined in that case.
    * 
    * @synopsis{
    * int end_mccp_compress()
    * }
    * 
    * @history{
    * introduced (3.3.447)
    * backported (3.2.10)
    * }
    * 
    * @see efun::start_mccp_compress(), efun::query_mccp(), efun::query_mccp_stats()
   **/
   int end_mccp_compress();
}
