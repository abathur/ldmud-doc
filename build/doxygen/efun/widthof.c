public class efun {
   /**
    * Returns the number of values per key of mapping \p map. If \p map is 0, the result is 0.
    * 
    * @synopsis{
    * int widthof(mapping map)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mapping m = ([ "foo": 1,2 ]);
    * widthof(m) // returns 2
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6)
    * }
    * 
    * @see efun::sizeof(), efun::mkmapping(), efun::m_reallocate(), efun::m_values(), efun::unmkmapping()
   **/
   int widthof(mapping map);
}
