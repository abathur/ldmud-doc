public class efun {
   /**
    * Strings and symbols are converted to an int array that consists of the args characters.
    * 
    * @par note: the string "12" will be converted to the array `({ 33, 34 })`, and not `({ 33, 34, 0 })` (the LDMud versions prior to 3.3 returned the latter array).
    * 
    * Quoted arrays are "dequoted", and arrays are left as they are.
    * 
    * Structs are converted into a normal array.
    * 
    * @par limit: The cast notation only works if the precise type of <value> is known at compile-time. This will not be fixed--use the function form instead.
    * 
    * @synopsis{
    * mixed * to_array(string)
    * mixed * to_array(symbol)
    * mixed * to_array(quotedarray)
    * mixed * to_array(mixed *)
    * mixed * to_array(struct)
    * (int*)<value>()
    * }
    * 
    * @history{
    * changed (3.3.250) -- added structs to the accepted data types.
    * }
    * 
    * @see efun::to_int(), efun::to_string(), efun::to_struct()
   **/
   (int*)<value>();
}
