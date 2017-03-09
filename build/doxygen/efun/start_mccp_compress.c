public class efun {
   /**
    * This efun must be called inside an interactive player and starts the compression of the driver -> client traffic.
    * 
    * Returns non-zero on success, and 0 on failure.
    * 
    * \p telopt denotes the @ref driver_topics_mccp "MCCP" version and must be either `TELOPT_COMPRESS2` or `TELOPT_COMPRESS` from <telnet.h>.
    * 
    * The only exception is when the telnet machine is disabled: then any value will do. This can be used with dedicated clients which send text uncompressed but expect to receive it compressed (Java clients using InflaterInputStream for example).
    * 
    * Available only if the driver is compiled with @ref driver_topics_mccp "MCCP" enabled; @ref driver_topics_predefined "__MCCP__" is defined in that case.
    * 
    * @headerfile <telnet.h>
    * 
    * @synopsis{
    * int start_mccp_compress(int telopt)
    * }
    * 
    * @history{
    * introduced (3.3.447/3.2.10)
    * changed (3.3.666) -- added the possibility to enable outgoing compression when the telnet machine is enabled (not backported to 3.2 series).
    * }
    * 
    * @see efun::end_mccp_compress(), efun::query_mccp(), efun::query_mccp_stats()
   **/
   int start_mccp_compress(int telopt);
}
