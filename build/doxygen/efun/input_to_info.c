public class efun {
   /**
    * Construct an array of all input_to's pending for this interactive
    * <player>.  The first entry in the array is the least recently added
    * input_to, the last element the most recently added one.
    * 
    * Every item in the array is itself an array of 2 or more entries:
    * 0:   The object (only if the function is a string).
    * 1:   The function (string or closure).
    * 2..: The argument(s).
    * 
    * @synopsis{
    * mixed * input_to_info(object player)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::input_to(), efun::find_input_to(), efun::remove_input_to(), efun::query_input_pending()
   **/
   mixed * input_to_info(object player);
}
