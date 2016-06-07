public class efun {
   /**
    * Returns the index of the first occurence of item in array arr,
    * or occurence of a character in a string. If not found, then -1
    * is returned.
    * 
    * If you want to search through an alist, use assoc() because
    * member_array() is good for unsorted but assoc() is faster for
    * sorted arrays.
    * 
    * @synopsis{
    * int member_array(mixed item, mixed *arr)
    * int member_array(mixed item, string arr)
    * }
    * 
    * @history{
    * removed (3.3) -- superseded by efun:member
    * }
    * 
    * @see efun::member(), @ref driver_LPC_mappings "mappings", efun::assoc(), efun::slice_array()
   **/
   int member_array(mixed item, string arr);
}
