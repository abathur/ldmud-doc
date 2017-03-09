public class efun {
   /**
    * Get information about all pending call outs. The result is an array in which every entry is itself an array describing one call_out. Each of these arrays consists of 3 or more elements:
    * 
    * 1. The object the function/closure is called in.
    * 2. The function or closure.
    * 3. The delay to go.
    * 4. The optional argument(s).
    * Callouts for destructed objects will not be contained in the list.
    * 
    * @synopsis{
    * mixed * call_out_info(void)
    * }
    * 
    * @see efun::call_out(), efun::remove_call_out(), efun::find_call_out()
   **/
   mixed * call_out_info(void);
}
