public class efun {
   /**
    * Create a new mapping with \p width values per key and fill it with the values from mapping \p m. If \p m has less than \p width values per key, the extra values in the result are set to 0. If \p m has more values per key, the extra values are ignored.
    * 
    * The mapping \p m is not changed.
    * 
    * @synopsis{
    * mapping m_reallocate(mapping m, int width)
    * }
    * 
    * @usage{
    * ~~~{.c}
    * mapping m = ([ "foo":1;2;3, "bar":4;5;6 ])
    * 
    * m_reallocate(m, 1) // returns ([ "foo":1,       "bar":4 ])
    * m_reallocate(m, 4) // returns ([ "foo":1;2;3;0, "bar":4;5;6;0 ])
    * 
    * ~~~
    * 
    * }
    * 
    * @history{
    * introduced (3.2.6) -- suggested by Tubmud.
    * }
    * 
    * @see efun::m_allocate(), efun::m_values(), efun::widthof()
   **/
   mapping m_reallocate(mapping m, int width);
}
