public class efun {
   /**
    * Returns an array with the values of mapping \p map. If \p index is given as a number between 0 and the width of the mapping, the values from the given column are returned, else the values of the first column.
    * 
    * @par note: The exact order of the values in the resulting arrays is not specified, and may vary after any change to the mapping. The only guarantee given is that if efun::m_indices() and efun::m_values() are taken at the same time, the order of both results is identical.
    * 
    * @synopsis{
    * mixed * m_values(mapping map)
    * mixed * m_values(mapping map, int index)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mapping m = ([ "foo":1;2;3, "bar":4;5;6, "baz":7;8;9 ])
    * m_values(m)    // returns ({ 1, 4, 7 }) or some permutation thereof
    * m_values(m, 0) // returns ({ 1, 4, 7 }) (ditto)
    * m_values(m, 1) // returns ({ 2, 8, 9 }) (ditto)
    * 
    * ~~~
    * 
    * }
    * 
    * @see efun::mappingp(), efun::mkmapping(), efun::m_indices(), efun::m_add(), efun::m_delete(), efun::sizeof(), efun::widthof(), efun::unmkmapping()
   **/
   mixed * m_values(mapping map, int index);
}
