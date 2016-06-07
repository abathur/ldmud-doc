public class efun {
   /**
    * transpose_array(({ ({1,2,3}), ({a,b,c}) }))
    * == ({ ({1,a}), ({2,b}), ({3,c}) })
    * 
    * transpose_array() applied to an alist results in an array of
    * ({ key, data }) pairs, useful if you want to use sort_array()
    * or filter() on the alist.
    * 
    * The given mapping 'map' is returned as an array of
    * `({ key, data })` pairs, sorted by the keys.
    * 
    * @synopsis{
    * mixed * transpose_array(mixed *arr)
    * }
    * 
    * @usage{
    * sort_array(transpose_array(({ m_indices(map), m_values(map) })),
    *        lambda(({ 'a, 'b }),
    *               ({ #'<, ({ #'[, 'a, 0 }),
    *                       ({ #'[, 'b, 0}) }) )
    * }
    * 
    * @see efun::sort_array()
   **/
   mixed * transpose_array(mixed *arr);
}
