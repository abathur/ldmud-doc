.. efun:: int send_erq(int request, string|int * data, closure callback)
  :include: <erq.h>

A request of given type (<request>, default is 0), equipped
with the given <data>, is sent to the erq. If <callback> is
set to a closure, it will be called when the response from the
erq (a status code) arrives, if the response carries enough data to
work on.

<request> can be one of the request codes defined in <erq.h>.
The binary flag ERQ_CB_STRING defines whether the <callback>
closure expects the returned data packed into an array of
integers or as a string.

<data> may be a string, or an array of integers which are then
interpreted as characters.

<callback>, if set, is a closure of either these forms:

  !ERQ_CB_STRING: void <closure>(int *response_data, int len)
   ERQ_CB_STRING: void <closure>(string response_data)

The result returned from the efun is 0 on failure to send the
data, or non-zero on a successful send.

The function causes a privilege violation "erq".

  .. history
Introduced in 3.2.1@61.
Made a privileged function in 3.2.1@84
LDMud 3.3.318 introduced the ERQ_CB_STRING flag.

  .. seealso:: :efun:`attach_erq_demon`, :concept:`erq`