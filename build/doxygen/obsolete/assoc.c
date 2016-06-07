public class efun {
   /**
    * All invocation forms search for a <key> in an <alist> (an array
    * of two equal-sized arrays) or in an ordered array <keys>.
    * An attempt to search in any other structure will yield an
    * unpredictable result.
    * 
    * Complexity: O(lg(n)), where n is the number of keys.
    * 
    * 1. Form: Key Search<key> is searched in the array <keys>, result is the index at
    * which <key> was found. If it isn't found, -1 is returned.
    * 2. Form: Alist Lookup<key> is searched in the <alist>, result is the data associated
    * with <key> if it is found. If it isn't found, the resultwill be 0, or <fail> if specified.
    * 3. Form: Ordered List Lookup<key> is searched in the array <keys>, the index at which it
    * is found is as index into <data> to get the return value.If <key> is not found, the reuslt will be 0, or <fail> ifspecified.For this to be useful, <data> has to be ordered so thatit matches <key>. This form of lookup is therefore usedprimarily with multidimensional alists.
    * The function is available only if the driver is compiled with
    * alist support. In that case, __ALISTS__ is defined.
    * 
    * @synopsis{
    * int assoc(mixed key, mixed *keys)
    * mixed assoc(mixed key, mixed *alist [, mixed fail])
    * mixed assoc(mixed key, mixed *keys, mixed *data [, mixed fail])
    * }
    * 
    * @history{
    * changed (3.3) -- made this an optional efun.
    * }
    * 
    * @see efun::insert_alist(), efun::order_alist()
   **/
   mixed assoc(mixed key, mixed *keys, mixed *data [, mixed fail]);
}
