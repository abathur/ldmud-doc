public class efun {
   /**
    * If \p verb is a string: remove the first action defined by the current object with the given \p verb from \p ob (default is `this_player()`). Return 1 if the action was found and removed, and 0 else.
    * 
    * If \p verb is a number: if non-0, remove all actions defined by the current object from \p ob (default is `this_player()`). Return the number of actions removed.
    * 
    * @synopsis{
    * int remove_action(int|string verb)
    * int remove_action(int|string verb, object ob)
    * }
    * 
    * @history{
    * introduced (3.2.1)
    * changed (3.2.10) -- added the ability to remove all actions.
    * }
    * 
    * @see efun::add_action(), efun::move_object()
   **/
   int remove_action(int|string verb, object ob);
}
