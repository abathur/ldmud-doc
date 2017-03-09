public class efun {
   /**
    * Flush output and send output directly with write <b>without IAC quoting</b>. The message may contain zeroes if given as int >>*<<. The messages go to `this_object()`, but only if it is interactive. It returns the number of characters actually written. Any 'allowed charset' setting is ignored.
    * 
    * Flag settings are interpreted bitwise and may be ored together (only for clients not using @ref driver_topics_mccp "MCCP" compression):
    * 
    * Bit 0 (value 1)
    * when set, `add_message()` is used instead of `write()`. Thus no previous flushing of the buffer is needed, but the output is not immediate, nor can the number of bytes actually sent be determined - the return value is undefined.
    * 
    * Bit 1 (value 2)
    * The buffer is flushed _after_ adding the message. Useful only in conjunction with Bit 0.
    * 
    * The idea behind the flag settings is that sending command codes for colours and other things needs to bypass the allowed charset filters, but isn't important enough to waste bandwith on a synchronous transmission.
    * 
    * @synopsis{
    * int binary_message(int *|string message, int flags)
    * }
    * 
    * @history{
    * introduced (3.2.1@40)
    * changed (3.2.1@60) -- Argument 'flags' introduced.
    * }
    * 
    * @see efun::set_connection_charset()
   **/
   int binary_message(int *|string message, int flags);
}
