public class efun {
   /**
    * @synopsis{
    * int remove_input_to(object player)
    * int remove_input_to(object player, string fun)
    * int remove_input_to(object player, closure fun)
    * int remove_input_to(object player, object fun)
    * int remove_input_to(object player, object ob, string fun)
    * }
    * 
   **/
   int remove_input_to(object player, object ob, string fun);
}
Remove a pending input_to from the interactive <player> object.
If the optional <fun> is not given, the most recently added input_to
is removed.

If the optional <fun> is given, the efun tries to find and remove the
most recently added input_to matching the <fun> argument:

   - <fun> is a string: the input_to functionname has to match
   - <fun> is an object: the object the input_to function is bound to
        has to match

   - <fun> is a closure: the input_to closure has to match.
   - <ob> and <fun> are given: both the object and the functionname
        have to match


Return 1 on success, or 0 on failure (no input_to found, object is
not interactive or has no input_to pending).

EXAMPLES
Remove all pending input_to from the current user, if any.

   while (remove_input_to(this_interactive())) ;

Introduced in LDMud 3.2.9 / 3.3.119.

   See Also: 
      efun::input_to(), efun::find_input_to(), efun::input_to_info(), efun::query_input_pending()
