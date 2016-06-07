public class efun {
   /**
    * @headerfile <telnet.h>
    * 
    * @synopsis{
    * int start_mccp_compress(int telopt)
    * }
    * 
   **/
   int start_mccp_compress(int telopt);
}
This efun must be called inside an interactive player and starts
the compression of the driver -> client traffic.

Returns non-zero on success, and 0 on failure.

<telopt> denotes the MCCP version and must be either TELOPT_COMPRESS2
or TELOPT_COMRESS from <telnet.h>.

The only exception is when the telnet machine is disabled: then
any value will do. This can be used with dedicated clients
which send text uncompressed but expect to receive it compressed
(Java clients using InflaterInputStream for example).

Available only if the driver is compiled with MCCP enabled;
__MCCP__ is defined in that case.

Added in LDMud 3.3.447, backported to LDMud 3.2.10.
LDMud 3.3.666 added the possibility to enable outgoing compression
when the telnet machine is enabled (not backported).

   See Also: 
      efun::end_mccp_compress(), efun::query_mccp(), efun::query_mccp_stats(), @ref driver_concepts_mccp "mccp"
