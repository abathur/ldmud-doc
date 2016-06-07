public class efun {
   /**
    * @synopsis{
    * int set_buffer_size(int size)
    * }
    * 
   **/
   int set_buffer_size(int size);
}
Changes the socket buffer size for this_interactive() to size,
up to a preconfigured maximum, result is the old buffer size
(or -1 on systems which aren't able to change the socket
buffer).

Modifying the buffer size may result in a better IO
throughput, but can also worsen it.

Introduced in @subpage driver_mailto:3.2.1@34 "3.2.1@34"
