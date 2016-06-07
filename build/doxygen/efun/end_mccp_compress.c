public class efun {
   /**
    * This efun must be called inside an interactive player and stops
    * the compression of the driver -> client traffic.
    * 
    * Returns non-zero on success, and zero on a failure.
    * 
    * Available only if the driver is compiled with MCCP enabled;
    * __MCCP__ is defined in that case.
    * 
    * @synopsis{
    * int end_mccp_compress()
    * }
    * 
   **/
   int end_mccp_compress();
}
