public class efun {
   /**
    * Sort the copy either by the ordering function ob->wrong_order(a, b),
    * or by the closure expression <cl>.
    * 
    * Usually a shallow copy of <arr> is made first and the sorted copy is
    * returned as result. However, if <arr> is given as a reference, no copy
    * will be made and <arr> will be sorted in-place.
    * 
    * If the <arr> argument equals 0, the result is also 0.
    * 
    * <ob> is the object in which the ordering function is called
    * and may be given as object or by its filename. If <ob> is omitted
    * or neither a string nor an object, it defaults to this_object().
    * 
    * The elements from the array to be sorted are passed in pairs to
    * the function <wrong_order> as arguments, followed by the <extra>
    * arguments if any.
    * 
    * The function should return a positive number if the elements
    * are in the wrong order. It should return 0 or a negative
    * number if the elements are in the correct order.
    * 
    * @synopsis{
    * mixed * sort_array(mixed *arr, string wrong_order)
    * mixed * sort_array(mixed *arr, string wrong_order, object|string ob)
    * mixed * sort_array(mixed *arr, string wrong_order, object|string ob, mixed extra...)
    * mixed * sort_array(mixed *arr, closure cl)
    * mixed * sort_array(mixed *arr, closure cl, mixed extra...)
    * }
    * 
    * @usage{
    * To sort an array
    * arr = ({ 3, 8, 1, 3 })
    * in ascending order with the help of the ordering function
    * int is_greater (int a, int b) {
    * 
    * return a > b;
    * 
    * }
    * the following uses of sort_array() are equivalent:
    * arr = sort_array(arr, "is_greater", this_object())
    * arr = sort_array(arr, "is_greater")
    * arr = sort_array(arr, #'is_greater)
    * arr = sort_array(arr, #'>)  (this is the preferred variant :-)
    * arr = sort_array(arr, lambda(({'a, 'b}), ({#'>, 'a, 'b})))
    * If no implicit shallow copy of <arr> should be made, pass <arr> as
    * reference:
    * sort_array(&arr, #'>)
    * A more complicated example is to sort the array
    * arr = ({ ({ "foo", 3 }), ({ "quux", 1 }), ... })
    * in ascending order by the second element of each subarray.
    * For this, the ordering function should be like
    * int is_greater (mixed *a, mixed *b) {
    * 
    * return a[1] > b[1];
    * 
    * }
    * }
    * 
   **/
   mixed * sort_array(mixed *arr, closure cl, mixed extra...);
}
