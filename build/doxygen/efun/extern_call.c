public class efun {
   /**
    * Returns zero, if the function that is currently being executed
    * was called by a local call, non-zero for call_other(), driver
    * applies, closure calls, etc. Currently the only return value
    * for them is 1, but later the various methods may be
    * distinguished by means of the return value.
    * 
    * @synopsis{
    * int extern_call()
    * }
    * 
   **/
   int extern_call();
}
