public class efun {
   /**
    * Return the connection charset of the current interactive in the form requested by \p mode:
    * 
    * - \p mode == `CHARSET_VECTOR`: return as bitvector
    * - \p mode == `CHARSET_STRING`: return as string
    * 
    * Alternatively, the status of the IAC quoting can be queried:
    * 
    * - \p mode == `CHARSET_QUOTE_IAC`: Return 0 if IACs are not quoted, return 1 if they are.
    * 
    * The bitvector is interpreted as an array of 8-bit-values and might contain up to 32 elements. Character n is "combinable" if `sizeof(bitvector) > n/8 && bitvector[n/8] & (1 << n%8)`.
    * 
    * If there is no current interactive, the function returns 0.
    * 
    * @headerfile <comm.h>
    * 
    * @synopsis{
    * mixed get_connection_charset(int mode)
    * }
    * 
    * @history{
    * introduced (3.2.10)
    * }
    * 
    * @see efun::set_connection_charset(), efun::get_combine_charset()
   **/
   mixed get_connection_charset(int mode);
}
