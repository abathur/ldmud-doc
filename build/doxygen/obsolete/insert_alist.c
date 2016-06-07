public class efun {
   /**
    * 1. Form: Alist InsertionThe <key> and all following <data> values are inserted
    * into the <alist>. If an entry for <key> already existsin the list, just the data values are replaced. The numberof <data> values must match the number of data arraysin the alist, naturally.Result is the updated <alist>.
    * 2. Form: Key InsertionInsert the <key> into the (ordered) array of <keys>, so that
    * subsequent assoc()s can perform quick lookups. Result is theindex at which <key> was inserted (or already found).
    * @par note:when working with string keys, the index might no longer
    * be valid after the next call to insert_alist().
    * 
    * Complexity: O(lg(n) + a*n) where n is the number of keys and
    * s is a very small constant (for block move);
    * 
    * The function is available only if the driver is compiled with
    * alist support. In that case, __ALISTS__ is defined.
    * 
    * @synopsis{
    * mixed * insert_alist(mixed key, mixed data..., mixed * alist)
    * int insert_alist(mixed key, mixed * keys)
    * }
    * 
    * @history{
    * changed (3.3) -- made this an optional efun.
    * }
    * 
    * @see efun::assoc(), efun::order_alist()
   **/
   int insert_alist(mixed key, mixed * keys);
}
