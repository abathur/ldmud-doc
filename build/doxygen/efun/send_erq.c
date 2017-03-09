public class efun {
   /**
    * A request of given type (\p request, default is 0), equipped with the given \p data, is sent to the erq. If \p callback is set to a closure, it will be called when the response from the erq (a status code) arrives, if the response carries enough data to work on.
    * 
    * \p request can be one of the request codes defined in <erq.h>. The binary flag `ERQ_CB_STRING` defines whether the \p callback closure expects the returned data packed into an array of integers or as a string.
    * 
    * \p data may be a string, or an array of integers which are then interpreted as characters.
    * 
    * \p callback, if set, is a closure of either these forms:
    * 
    * !ERQ_CB_STRING: void <closure>(int >>*<<response_data, int len)
    *    ERQ_CB_STRING: void <closure>(string response_data)
    *    
    * The result returned from the efun is 0 on failure to send the data, or non-zero on a successful send.
    * 
    * The function causes a privilege violation "erq".
    * 
    * @headerfile <erq.h>
    * 
    * @synopsis{
    * int send_erq(int request, string|int * data, closure callback)
    * }
    * 
    * @history{
    * introduced (3.2.1@61)
    * changed (3.2.1@84) -- Made a privileged function
    * changed (3.3.318) -- introduced the ERQ_CB_STRING flag.
    * }
    * 
    * @see efun::attach_erq_demon()
   **/
   int send_erq(int request, string|int * data, closure callback);
}
