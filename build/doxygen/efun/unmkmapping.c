public class efun {
   /**
    * Take mapping \p map and return an array of arrays with the keys and values from the mapping.
    * 
    * The return array has the form `({ keys[], data0[], data1[], ... })`, with `keys[]` being the array of all keys, `data0[]` the array of all values in the first column, `data1[]` the array of all values in the second column, etc. In particular, the data for `key[x]` is stored in `data0[x]`, `data1[x]`, etc.
    * 
    * efun::unmkmapping() is inverse to efun::mkmapping(), so `apply(#'mkmapping, unmkmapping(m)) == m`.
    * 
    * @synopsis{
    * mixed * unmkmapping(mapping map)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mapping m = ([ 1:10;20, 2:11;21 ]);
    * unmkmapping(m)
    * // returns ({ ({1, 2}), ({ 10, 11 }), ({ 20, 21 }) })
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * }
    * 
    * @see @ref driver_syntax_mappings "mapping", efun::mappingp(), efun::m_indices(), efun::m_values(), efun::m_delete(), efun::sizeof(), efun::widthof()
   **/
   mixed * unmkmapping(mapping map);
}
