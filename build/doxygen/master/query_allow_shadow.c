public class master {
   /**
    * Return 1 if `previous_object()` is allowed to use efun::shadow() on object \p victim, 0 if it is not.
    * 
    * The function should deny shadowing on all root objects, else it might query the victim for clearance. Most installations seem to use `victim->prevent_shadow(previous_object())` to check if the victim denies being shadowed.
    * 
    * @synopsis{
    * int query_allow_shadow(object victim)
    * }
    * 
    * @see efun::shadow()
   **/
   int query_allow_shadow(object victim);
}
