public class efun {
   /**
    * Applied to an alist, results in an array of `({ key, data })` pairs, useful if you want to use efun::sort_array() or efun::filter() on the alist.
    * 
    * @synopsis{
    * mixed * transpose_array(mixed *arr)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * transpose_array(({ ({1,2,3}), ({a,b,c}) }))
    * // returns ({ ({1,a}), ({2,b}), ({3,c}) })
    * 
    * ~~~
    * The mapping 'map' in the example below is returned as an array of `({ key, data })` pairs, sorted by the keys.:
    * 
    * ~~~{.c}
    * sort_array(transpose_array(({ m_indices(map), m_values(map) })),
    *        lambda(({ 'a, 'b }),
    *               ({ #'<, ({ #'[, 'a, 0 }),
    *                       ({ #'[, 'b, 0}) }) )
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::sort_array()
   **/
   mixed * transpose_array(mixed *arr);
}
