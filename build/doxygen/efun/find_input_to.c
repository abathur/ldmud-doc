public class efun {
   /**
    * Find the input_to most recently added to the interactive <player>
    * object matching the <fun> argument:
    * 
    * - <fun> is a string: the input_to functionname has to match
    * - <fun> is an object: the object the input_to function is bound to
    *      has to match
    *      
    * - <fun> is a closure: the input_to closure has to match.
    * - <ob> and <fun> are given: both the object and the functionname have
    *      to match
    *      
    * 
    * Return -1 if not found, or the position in the input_to stack (0
    * being _least_ recently added input_to).
    * 
    * @synopsis{
    * int find_input_to(object player, string fun)
    * int find_input_to(object player, closure fun)
    * int find_input_to(object player, object fun)
    * int find_input_to(object player, object ob, string fun)
    * }
    * 
   **/
   int find_input_to(object player, object ob, string fun);
}
