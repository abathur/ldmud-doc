public class efun {
   /**
    * Creates an alist.
    * 
    * Either takes an array containing keys, and others containing
    * the associated data, where all arrays are to be of the same
    * length, or takes a single array that contains as first member
    * the array of keys and has an arbitrary number of other members
    * containing data, each of wich has to be of the same length as
    * the key array. Returns an array holding the sorted key array
    * and the data arrays; the same permutation that is applied to
    * the key array is applied to all data arrays.
    * 
    * Complexity is O(n * lg(n) + n * m), where n is the number of
    * elements in the key array and m is the number of data arrays + 1.
    * 
    * Note that the dimensions of the arrays are used the other
    * way than in lisp to allow for faster searching.
    * 
    * Keys have to be of type integer, string or object. Types can
    * be mixed.
    * 
    * The function is available only if the driver is compiled with
    * alist support. In that case, __ALISTS__ is defined.
    * 
    * @synopsis{
    * mixed * order_alist(mixed *keys, mixed *|void data, ...)
    * }
    * 
    * @history{
    * changed (3.3) -- made this an optional efun
    * }
    * 
    * @see @ref driver_LPC_mappings "mappings", efun::insert_alist(), efun::assoc(), efun::transpose_array()
   **/
   mixed * order_alist(mixed *keys, mixed *|void data, ...);
}
