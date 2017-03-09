public class efun {
   /**
    * Changes the socket buffer size for `this_interactive()` to \p size, up to a preconfigured maximum, result is the old buffer size (or -1 on systems which aren't able to change the socket buffer).
    * 
    * Modifying the buffer size may result in a better IO throughput, but can also worsen it.
    * 
    * @synopsis{
    * int set_buffer_size(int size)
    * }
    * 
    * @history{
    * introduced (3.2.1@34)
    * }
    * 
   **/
   int set_buffer_size(int size);
}
