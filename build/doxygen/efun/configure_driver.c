public class efun {
   /**
    * This efun configures runtime adjustable bahviour of the driver.
    * 
    * Sets the option \p what to the value \p data.
    * 
    * This function always causes the privilege_violation ("configure_driver", this_object(), what, data).
    * 
    * \p what == `DC_MEMORY_LIMIT`
    * Set new soft and hard memory limits for the driver. \p data is expected to be an array with two elements, which have to be integers giving the amount of memory in bytes. `({<soft memory limit>, <hard memory limit>})`
    * 
    * \p what == `DC_ENABLE_HEART_BEATS`
    * Globally enable the calling of Heartbeats, if \p data is 1, globally disable them if \p data is 0. If called during heartbeat processing, the change comes into effect at the next backend cycle.
    * 
    * \p what == `DC_LONG_EXEC_TIME`
    * Set the time considered as (too) long for top-level executions. If an execution exceeds this time, a stack trace will be written to the debug log. The execution will continue at that point. \p data is an integer and measured in microseconds. A time of 0 disables the detection of long executions.
    * 
    * \p what == `DC_DATA_CLEAN_TIME`
    * Sets the average time between clean-ups of an objects data structures. This is not to be confused with the standard cleanup time which determines when @ref driver_hook_clean_up "H_CLEAN_UP" is called. A long time for data cleanup may lead to larger memory consumption and prevents destructed objects being cleaned up. A too short time may lead to high loads and lag on the machine. The actual time delay will be a time between `0.9*DC_DATA_CLEAN_TIME` and `1.1*DC_DATA_CLEAN_TIME`. Default at driver startup are 3600s. \p data is an integer and measured in seconds.
    * 
    * \p what == `DC_TLS_CERTIFICATE`
    * Sets the current certificate used for new TLS sessions. It can be one of the certificates in the key directory (command line option --tls-keydirectory) or the main certificate (given with --tls-certfile). Default is the main certificate or else the first certificate found in the directory. The chosen certificate at the time of the efun::tls_init_connection() call is used for that connection. \p data is a string containing the SHA1 fingerprint of the certificate with hexadecimal numbers, it may contain colons or whitespaces (for example `5A:FE:CA:57:1E:50:5E:1E:C7:ED:BA:11:AD:50:10:75:0F:7A:1E:50`). When loading certificates their fingerprints are printed on stdout and into the logfile.
    * 
    * @headerfile <configuration.h>
    * 
    * @synopsis{
    * void configure_driver(int what, mixed data)
    * }
    * 
    * @history{
    * introduced (3.3.719)
    * changed (3.5.0) -- added DC_ENABLE_HEART_BEATS, DC_LONG_EXEC_TIME, DC_DATA_CLEAN_TIME, DC_TLS_CERTIFICATE was added in 3.5.0.
    * }
    * 
    * @see efun::configure_interactive()
   **/
   void configure_driver(int what, mixed data);
}
