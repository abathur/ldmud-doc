public class efun {
   /**
    * Find the input_to most recently added to the interactive \p player object matching the \p fun argument:
    * 
    * - \p fun is a string: the input_to functionname has to match
    * - \p fun is an object: the object the input_to function is bound to has to match
    * - \p fun is a closure: the input_to closure has to match.
    * - \p ob and \p fun are given: both the object and the functionname have to match
    * 
    * Return -1 if not found, or the position in the input_to stack (0 being _least_ recently added input_to).
    * 
    * @synopsis{
    * int find_input_to(object player, string fun)
    * int find_input_to(object player, closure fun)
    * int find_input_to(object player, object fun)
    * int find_input_to(object player, object ob, string fun)
    * }
    * 
    * @history{
    * introduced (3.2.9)
    * }
    * 
    * @see efun::input_to(), efun::input_to_info(), efun::remove_input_to(), efun::query_input_pending()
   **/
   int find_input_to(object player, object ob, string fun);
}
